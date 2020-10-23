# R6SDK  
A Software Development Kit for the game Rainbow Six: Siege  
# ChatManager  
bool is_open();  -> Returns 1 if chat is open
void set_status(bool status); -> Set the chat status (1 open 0 closed)
int get_type(); -> Returns the chat type (1 = team, 0 = all)
void set_type(int type); -> Set the chat type
void set_message(std::string message); -> Set the message to send
std::vector<Chat_log> log_messages(); -> Returns msglog struct including sender and message