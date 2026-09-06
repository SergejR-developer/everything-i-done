import pandas as pd
import webbrowser


#-----------FILES-------------
metadata = 'https://www.cnb.cz/cs/statistika/' \
'menova_bankovni_stat/seznamy-instituci-pro-potreby-menove-a-financni-statistiky/' \
'seznam-investicnich-fondu/seznam-if-vysvetlivky/'

file = 'fki_cz.xlsx'
#-----------------------------

def check_metadata(data):

    webbrowser.open(data)

def parse_xlsx(path):

    xlsx = pd.ExcelFile(path)

    df = xlsx.parse(0, header=0, index_col=None, skiprows=[0, 1, 2])

    return df

def rename(df, old, new):
    
    df.rename(columns=dict(zip(old, new)), inplace=True)

opportunities = parse_xlsx(file)

old_names = [opportunities.columns[i] for i in range(17)]
new_names = ['riad_code', 'country', 'id', 
            'id_res', 'lei', 'name',
            'street', 'city', 'post',
            'category', 'public_private',
            'structure_1', 'structure_2', 'subfond',
            'isin', 'report', 'manager']

rename(opportunities, old_names, new_names)

print(opportunities.head())