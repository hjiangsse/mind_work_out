from clickhouse_driver import Client
import time

def simple_test():
    start = time.time()
    client = Client(host='192.168.2.129', password='jiang186212')
    print(time.time() - start)

    client.execute('show databases')
    client.execute('use tutorial')

    select_query = '''
                    SELECT       
                        CounterID,
                        Sign,
                        IsNew,
                        VisitID,
                        UserID,
                        Duration,
                        PageViews,
                        Hits
                    FROM tutorial.visits_v1
                    WHERE StartDate BETWEEN '2014-03-01' AND '2014-03-30'
                    '''
    start = time.time()
    select_res = client.execute(select_query)
    print(time.time() - start)
    print(len(select_res))


if __name__ == "__main__":
    simple_test()