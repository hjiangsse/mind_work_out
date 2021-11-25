import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

def gen_close_prices(loc, scale, size):
    return np.random.normal(loc = loc, scale = scale, size = size)

def main():
    close_data = gen_close_prices(10.0, 1.0, 1000)
    open_data = np.roll(close_data, 1)
    high_data = np.where((open_data > close_data), open_data, close_data)
    low_data = np.where((open_data <= close_data), open_data, close_data)
    open_data[0], close_data[0], high_data[0], low_data[0] = np.NAN, np.NAN, np.NAN, np.NAN
    data_index = pd.date_range("2021-10-01", freq='D', periods=1000)
    df_stock = pd.DataFrame({'close': close_data, 'open': open_data, 'high': high_data, 'low': low_data}, index=data_index)
    
    volumn_data = np.random.randint(10000, 20000, size=1000)
    df_volume = pd.DataFrame({'volume': volumn_data}, index=data_index)
    
    #get some messages of the dataframe
    print(df_stock.head())
    print(df_stock.tail())
    print(df_stock.columns)
    print(df_stock.index)
    print(df_stock.shape)
    print(df_stock.describe())
    print(df_stock.info())

    '''
    df_visual = df_stock.loc['2021-10-01':'2022-10-01', ['high', 'low']].plot(linewidth=1, figsize=(8,6))
    df_visual.set_xlabel('Time')
    df_visual.set_ylabel('High and Low price')
    df_visual.set_title('From 2021-10-01 to 2022-10-01')
    df_visual.legend()
    plt.show()
    '''

    print(df_stock.isnull().head())
    print(df_stock.notnull().head())
    print(df_stock[df_stock.isnull().T.any().T])

    df_fillna = df_stock.fillna(method='bfill', axis=0)
    print(df_fillna.head())


if __name__ == "__main__":
    #main()
    csvload = pd.read_csv('test.csv', parse_dates=True, index_col=0, encoding='gb2312')
    print(csvload)
    print("")
    print("国庆节期间共花费： ", csvload['开销'].sum())
    print("")
    print("每日开销明细：")
    print(csvload.resample('D', closed='left', label='left').sum())