#include "includes.h"
R6* r6;

R6::R6() {
	this->mem = new Memory();
	this->Chat = new ChatManager();
}

int main() {
	r6 = new R6();
	r6->mem->setup();
	
	r6->Chat->get();
	std::vector<ChatManager::Chat_log>Messages =  r6->Chat->log_messages();
	for (auto message : Messages) {
		std::printf("%s said: %s\n", message.Prefix.c_str(), message.Message.c_str());
	}
	
	while (true) {
		if (r6->Chat->is_open())
			printf("Chat is open\n");
		r6->Chat->set_status(1);//Open
		r6->Chat->set_message("ABCDEF");
		r6->Chat->set_type(ChatManager::ChatType::TEAM);
		//DeviceManager->PressKey(Enter);
		Sleep(100);
	}

	
	system("pause");
}