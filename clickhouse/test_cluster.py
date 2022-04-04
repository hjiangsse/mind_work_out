from clickhouse_driver import Client

if __name__ == "__main__":
    client = Client(host='localhost')
    create_database_query = "CREATE DATABASE IF NOT EXISTS company_db ON CLUSTER \'company_cluster\'"
    client.execute(create_database_query)

    create_table_query = """
    CREATE TABLE IF NOT EXISTS company_db.events ON CLUSTER 'company_cluster' (
    time DateTime,
    uid  Int64,
    type LowCardinality(String)
    )
    ENGINE = ReplicatedMergeTree('/clickhouse/tables/{cluster}/{shard}/table', '{replica}')
    PARTITION BY toDate(time)
    ORDER BY (uid);
    """
    client.execute(create_table_query)

    create_table_distr_query = """
    CREATE TABLE IF NOT EXISTS company_db.events_distr ON CLUSTER 'company_cluster' AS company_db.events
    ENGINE = Distributed('company_cluster', company_db, events, uid);
    """
    client.execute(create_table_distr_query)

    insert_query = """
    INSERT INTO company_db.events_distr VALUES
    ('2020-01-01 10:00:00', 100, 'view'),
    ('2020-01-01 10:05:00', 101, 'view'),
    ('2020-01-01 11:00:00', 100, 'contact'),
    ('2020-01-01 12:10:00', 101, 'view'),
    ('2020-01-02 08:10:00', 100, 'view'),
    ('2020-01-03 13:00:00', 103, 'view');
    """
    client.execute(insert_query)
