from pssh.clients import ParallelSSHClient

client = ParallelSSHClient(['192.168.222.245', '192.168.222.246'], user='jingle', password='Life123')
output = client.run_command('lscpu')
for host_out in output:
    for line in host_out.stdout:
        print(line)
    exit_code = host_out.exit_code
