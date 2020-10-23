class ChatManager {
private:
	uintptr_t address;
	

	static const DWORD max_msg_size = 0x7F;
public:
	void get();

	struct Chat_log {
		std::string Message;
		std::string Prefix;
	};

	enum ChatType : int {
		ALL,
		TEAM
	};

	//
	bool is_open();
	void set_status(bool status);
	//
	int get_type();
	void set_type(int type);
	//
	void set_message(std::string message);
	//
	std::vector<Chat_log> log_messages();
};