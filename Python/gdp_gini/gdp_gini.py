import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

#Read csvs from World Bank DB and fill nas
df_gdp = pd.read_csv('gdp.csv').fillna(0)
df_gini = pd.read_csv('gini.csv').fillna(0)

#Drop useless columns
cols_to_drop = ['Indicator Name', 'Indicator Code']
df_gdp = df_gdp.drop(columns=cols_to_drop)
df_gini = df_gini.drop(columns=cols_to_drop)

def get_last(df, indicator_name):
    #Create a column in a DataFrame with last observation of the indicator
    temp = []
    for index, row in df.iterrows():
        temp.append(0)
        for col in df.drop(columns=['Country Name', 'Country Code']).columns:
            if row[col] != 0 :
                temp.pop()
                temp.append(row[col])
            else : pass
    df[indicator_name] = temp

get_last(df_gdp, 'Last_GDP')
get_last(df_gini, 'Last_GINI')

df_gdp['Last_GDP'] = [x / 100000 for x in df_gdp['Last_GDP']]
df_gdp.rename(columns={'Last_GDP' : 'Last_GDP (100,000$)'}, inplace=True)

#Drop columns for individual years and merge two tables
df_gdp = df_gdp[['Country Name', 'Country Code', 'Last_GDP (100,000$)']]
df_gini = df_gini[['Country Name', 'Country Code', 'Last_GINI']].query('Last_GINI != 0')
df_gdp_gini = df_gdp.merge(df_gini, how = 'inner', on=['Country Name', 'Country Code'])

df_gdp_gini.plot(x='Last_GDP (100,000$)', y='Last_GINI', kind='scatter')

x = list(df_gdp_gini['Last_GDP (100,000$)'])
y = list(df_gdp_gini['Last_GINI'])

for i, txt in enumerate(df_gdp_gini['Country Code']):
    plt.annotate(txt, xy=(x[i], y[i]))

plt.xscale('log')
plt.show()