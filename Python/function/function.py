import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

def function(x, a, b=0, c=0, d=0, kind='identity'):
    #TODO
    if a == 0: raise ValueError('constant with x cannot be equal to 0')
    match kind:
        case 'identity':
            y = a * x + b
            df = pd.DataFrame({'x':x, 'y':y})

            sns.lineplot(data=df, x='x', y='y')
            plt.grid(1)
            plt.xticks(df['x'])
            plt.yticks(df['y'])
            plt.xlim(df.iloc[0, 0], df.iloc[-1, 0])
            plt.ylim(df.iloc[0, 1], df.iloc[-1, 1])
            plt.show()

            return df
        
        case 'absolute':
            y = a * abs(x) + b
            df = pd.DataFrame({'x':x, 'y':y})

            sns.lineplot(data=df, x='x', y='y')
            plt.grid(1)
            plt.xticks(df['x'])
            plt.yticks(df['y'])
            plt.xlim(df.iloc[0, 0], df.iloc[-1, 0])
            plt.show()

            return df
        
        case 'quadratic':
            y =  a * x**2 + b * x + c
            df = pd.DataFrame({'x':x, 'y':y})

            sns.lineplot(data=df, x='x', y='y')
            plt.grid(1)
            plt.xticks(df['x'])
            plt.xlim(df.iloc[0, 0], df.iloc[-1, 0])
            plt.show()

            return df
        
        case 'cubic':
            y = a * x**3 + b * x**2 + c * x + d
            df = pd.DataFrame({'x':x, 'y':y})

            sns.lineplot(data=df, x='x', y='y')
            plt.grid(1)
            plt.xticks(df['x'])
            plt.xlim(df.iloc[0, 0], df.iloc[-1, 0])
            plt.show()

            return df
        
        case 'root':
            zero_index = np.where(x == 0)
            new_x = np.delete(x, zero_index)

            y = a * new_x**(1/2) + b
            df = pd.DataFrame({'x':new_x, 'y':y})

            sns.lineplot(data=df, x='x', y='y')
            plt.grid(1)
            plt.xticks(df['x'])
            plt.xlim(df.iloc[0, 0], df.iloc[-1, 0])
            plt.show()

            return df
        
        case 'croot': #TODO
            zero_index = np.where(x == 0)
            new_x = np.delete(x, zero_index)
            
            y = a * new_x**(1/3) + b
            df = pd.DataFrame({'x':new_x, 'y':y})

            sns.lineplot(data=df, x='x', y='y')
            plt.grid(1)
            plt.xticks(df['x'])
            plt.yticks(df['y'])
            plt.xlim(df.iloc[0, 0], df.iloc[-1, 0])
            plt.ylim(df.iloc[0, 1], df.iloc[-1, 1])
            plt.show()

            return df
        
        case 'reci':
            zero_index = np.where(x == 0)
            new_x = np.delete(x, zero_index)
            y = a * 1/new_x + b
            df = pd.DataFrame({'x':new_x, 'y':y})

            sns.lineplot(data=df, x='x', y='y')
            plt.grid(1)
            plt.xticks(df['x'])
            plt.xlim(df.iloc[0, 0], df.iloc[-1, 0])
            plt.show()

            return df
        
        case 'reci_sq':
            zero_index = np.where(x == 0)
            new_x = np.delete(x, zero_index)
            y = a * 1/(new_x**2) + b
            df = pd.DataFrame({'x':new_x, 'y':y})

            sns.lineplot(data=df, x='x', y='y')
            plt.grid(1)
            plt.xticks(df['x'])
            plt.xlim(df.iloc[0, 0], df.iloc[-1, 0])
            plt.show()

            return df
        
x = np.array([x for x in range(-10, 11)])
a = 1
b = 0

df_func = function(x, a, b, kind='quadratic')