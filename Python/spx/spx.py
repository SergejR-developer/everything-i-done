import pandas as pd

#---------Declaring -----------------------

data = ["s&p500_2024.csv", "s&p500_2023.csv", "s&p500_2025.csv"]
lower_threshold = 0.98
upper_threshold = 1.02

#---------Creating DataFrame---------------

def make_df(list_dfs):
    large_df = pd.DataFrame()
    for df in list_dfs:
        large_df = pd.concat([large_df, pd.read_csv(df, sep=",", thousands=",", decimal=".")], ignore_index=True)

    return large_df

df = make_df(data)


#---------Setting types and sorting dataframe-------------------

df["Date"] = pd.to_datetime(df["Date"])

df[["Open","High","Low","Close"]] = df[["Open","High","Low","Close"]].astype("float32")

df = df.sort_values(by="Date").reset_index(drop=True)

#---------Finding and marking Index--------

df["Index"] = df["Close"].values / df["Open"].values

df["Mark"] = df["Index"].map(lambda value: ("WW" if value > upper_threshold else "W") if value > 1 else ("LL" if value <= lower_threshold else "L"))
df["Mark"] = df["Mark"].astype("category")

#---------Creating conditional lists-------

after_wins = []
after_loses = []
after_crashes = []
after_rally = []

for i in range(0, len(df)-1):
    if df["Mark"].values[i] == "WW": after_rally.append(df["Mark"].values[i+1])
    elif df["Mark"].values[i] == "W": after_wins.append(df["Mark"].values[i+1])
    elif df["Mark"].values[i] == "L": after_loses.append(df["Mark"].values[i+1])
    else: after_crashes.append(df["Mark"].values[i+1])

def serialization(marked_list):

    series = pd.Series(marked_list, dtype="category")
    series = series.cat.set_categories(["WW", "W", "L", "LL"])
    
    return series

wins_series = serialization(after_wins)
loses_series = serialization(after_loses)
crashes_series = serialization(after_crashes)
rally_series = serialization(after_rally)

#---------Printing the probability table---

def printing_head():
    
    pr = round(df["Mark"].value_counts(normalize=True).loc["WW"], 3)
    pw = round(df["Mark"].value_counts(normalize=True).loc["W"], 3)
    pl = round(df["Mark"].value_counts(normalize=True).loc["L"], 3)
    pc = round(df["Mark"].value_counts(normalize=True).loc["LL"], 3)
    
    print( f"P[rally] = {pr} \nP[win] = {pw} \nP[loss] = {pl} \nP[crash] = {pc}\n")

    return

def printing(event=None):
    match event:
        case "rally": mark = "WW"
        case "win": mark = "W"
        case "loss": mark = "L"
        case "crash": mark = "LL"
    
    pr = round(rally_series.value_counts(normalize=True).loc[mark], 3)
    pw = round(wins_series.value_counts(normalize=True).loc[mark], 3)
    pl = round(loses_series.value_counts(normalize=True).loc[mark], 3)
    pc = round(crashes_series.value_counts(normalize=True).loc[mark], 3)

    print(
            f"P[{event} to rally] = {pr}\t\t"
            f"P[{event} to win] = {pw}\t\t"
            f"P[{event} to loss] = {pl}\t\t"
            f"P[{event} to crash] = {pc}\n"
        )
    
    return

printing_head()
printing("rally")
printing("win")
printing("loss")
printing("crash")
print(df.head())