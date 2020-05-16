from Plugin_Observer import plugin # import the plugin class
from bin import pynat # import the api so we will be able to access the packets 

class ExamplePlugin(plugin): # create a class, derive from plugin. Name NUST be the same as the file and folder name!!
    def init (self):
        plugin _init_(self, "ExamplePlugin", # name (should be the same as file and folder name of the plugin. The folder MUST be placed in the Plugins directory.)
        "Elad Mafia", # author (me!)
        0.1, # version
        "This plugin is just an example, it does absolutely nothing", # description
        "Example", # type
        5, # priority
        None, # db pointer, usually starts as null
        ["get_log", "delete_database")) # list of actions
        #add more fields if you want 
        
        
    def process(self, packet):
    # this function runs for every packet!
    # pay attention - I imported the api so I can access the packets!
    src_addr = ""
    dst_addr = ""
    ips = pynat.get_ips(packet) # this function takes the packet id provided and returns the packets dst and src ips
    if ips = None: return packet * #check if the packet has ip layer
    src_addr, dst_addr = ips(0], ips[1] # assign the ips accordingly 
    # now you can do whatever:
    if src addr = "127.0.0.1":
        return None # return None if you wish to drop the packet
    # simply log every packet - dummy example
    pynat.exec_db(self.db, "INSERT OR IGNORE INTO LOG VALUES ('{}', '{}', strftime('%Y-%m-%d %H:%M', 'now', 'localtime'))".format(src_addr, dst_addr))
    return Packet # return the packet if you wish the forward the packet 
    
    
    def setup(self):
        # do the follwing every time the plugin starts
        file_location = os.path.dirname(__file__) # get the path of the current file
        self.db = pynat.open_db(file_location + "/{}.db".format(self.name)) # create / open db
        # create table if it doesn't exist (using pynat database functions the operations are faster the python's version)
        pynat.exec_db(self.db, "CREATE TABLE IF NOT EXISTS LOG (SRC_IP TEXT NOT NULL, DST_IP TEXT NOT HULL, TIME TEXT NOT HULL, UNIQUE(SRC_IP, BLOCKED_IP, THE) ")
        # Do whatever 
        
    def teardown(self):
        # called everytime the plugin closes
        # close db
        pynat.close_db(self.db) 
        
    def get_actions(self): 
    # returning action list
        return stlf.actions 

    
    # You HAVE to add functions with the same name as the actions specified in the action list, to handle the action.
    def get_log(self):
    answer_array = []
    db_res = pynat.select_db(self.db, "SELECT * FROM LOG") # select from log
    for entry in db_res:
        answer_array.append("SRC_IP:": entry[0], "DST_IP": entry[1], "TIME": entry[2]) 
    return {"result": answer_array} #return as json. key MUST be result!! 
    
    def delete_database(self):
        pynat.exec_db(self.db, "DELETE FROM LOG") # delete the log
        return ("status": "success") # has to return status! 

