import subprocess


MAC_LENGTH = 17


def get_connected_devices(adapter):
    macs = []

    process = subprocess.Popen(['iw', 'dev', adapter, 'station', 'dump'],\
         stdout=subprocess.PIPE)
    output = process.communicate()[0].decode()

    begin = output.find("Station ") + len("Station ")
    num_of_stations = output.count("Station ")

    for i in range(num_of_stations):
        macs.append(output[begin:begin+MAC_LENGTH])
        begin = output.find("Station ", begin) + len("Station ")
    
    return macs


if  __name__ == "__main__":
    get_connected_devices("ap0") # for debugging purposes