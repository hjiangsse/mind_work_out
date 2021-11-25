from datetime import date, time, datetime, timedelta
import pandas as pd
from pandas.core.indexes import period
import numpy as np

def test_resolution():
    print(f'date.resolution: {date.resolution}')
    print(f'time.resolution: {time.resolution}')
    print(f'datetime.resolution: {datetime.resolution}')

def test_interval():
    print(f'date.max: {date.max}, date.min: {date.min}')
    print(f'time.max: {time.max}, time.min: {time.min}')
    print(f'datetime.max: {datetime.max}, datetime.min: {datetime.min}')

def create_datetime():
    datetime_obj = datetime(2021, 10, 3, 7, 31, 0, 0)
    print(f'datetime: {datetime_obj}')

def test_format():
    datetime_obj = datetime(2021, 10, 3, 7, 31, 0, 0)
    print(f'original datetime: {datetime_obj}')
    replace_datetime = datetime_obj.replace(day=4, hour=10)
    print(f'replace datetime: {replace_datetime}')    
    print(f'iso format: {replace_datetime.isoformat()}')
    print(f'strfmt time: {replace_datetime.strftime("%Y-%m-%d %X")}')
    print(f'datetime.strptime(): {datetime.strptime("2021-10-03", "%Y-%m-%d")}')
    print(f'current time: {datetime.now().timestamp()}')
    cur_timestamp = datetime.now().timestamp()
    cur_timestamp_next = cur_timestamp + 1000
    print(f'cur_timestamp_next to date: {datetime.fromtimestamp(cur_timestamp_next)}')

def test_delta():
    dtobj1 = datetime(2021,10,3,7,31,0,0)
    dtobj2 = datetime(2021,10,3,7,45,0,0)
    print((dtobj2 - dtobj1).seconds/60)
    print(dtobj1 - dtobj2)
    #get now and next now, this is a add
    print(f' now: {datetime.now()}, next now: {datetime.now() + timedelta(days=1)}')

def test_pandas_timestamp():
    ts1 = pd.Timestamp(2021, 10, 3, 10, 10, 10)
    print(f'ts-1: {ts1}')
    ts2 = pd.Timestamp(datetime(2021, 10, 3, 10, 10, 10))
    print(f'ts-2: {ts2}')
    ts3 = pd.Timestamp("2021-10-03")
    print(f'ts-3: {ts3}')
    print(type(ts1))
    ts4 = pd.to_datetime("2021-10-03")
    print(f'ts-4: {ts4}')
    ts5 = pd.to_datetime(datetime(2021, 10, 3, 10, 10, 10))
    print(f'ts-5: {ts5}')
    ts6 = pd.to_datetime(['2021-01-01', '2021-01-02', '2021-01-03'])
    print(ts6)
    ts7 = ts6 + pd.Timedelta(days=1)
    print(ts7)

def test_pandas_timerange():
    date_rng = pd.date_range('2021-01-01', freq='M', periods=12)
    print(date_rng)
    period_rng = pd.period_range('2021-01-01', freq='M', periods=12)
    print(period_rng)
    sun_date_rng = pd.date_range('2021-10-01', freq='W-SUN', periods=12)
    print(sun_date_rng)
    sun_period_rng = pd.period_range('2021-10-01', freq='W-SUN', periods=12)
    print(sun_period_rng)
    hour_date_rng = pd.date_range('2021-10-01', freq='H', periods=12)
    print(hour_date_rng)
    hour_period_rng = pd.period_range('2021-10-01', freq='H', periods=12)
    print(hour_period_rng)

def test_pandas_resample():
    rng = pd.date_range('2021-10-01', freq='D', periods=12) 
    test_data = pd.Series(np.arange(1, 13), index = rng)
    print(test_data.resample('5D', closed='left', label='left').sum())  
    print(test_data.resample('5D', closed='right', label='right').sum()) 
    ts_12h_asfreq = test_data.resample('12H').asfreq()
    print(ts_12h_asfreq)
    ts_12h_ffill = test_data.resample('12H').ffill()
    print(ts_12h_ffill)
    ts_12h_bfill = test_data.resample('12H').bfill()
    print(ts_12h_bfill)

def main():
    test_resolution()
    test_interval()
    create_datetime()
    test_format()
    test_delta()
    test_pandas_timestamp()
    test_pandas_timerange()
    test_pandas_resample()

if __name__ == "__main__":
    main()