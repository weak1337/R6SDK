#include "includes.h"
extern R6* r6;
void ChatManager::get() {
	uintptr_t ChatBase = r6->mem->read<uintptr_t>(r6->base + 0x6E09928); //b9 ? ? ? ? 48 03 0d ? ? ? ? e8 ? ? ? ? 48 8b 40 ? 48 85 c0 74 ? 48 8b 40 ? f6 80 ? ? ? ? ? 75 ? 80 be
	uintptr_t Ref1 = r6->mem->read<uintptr_t>(ChatBase + 0x2D8);
	uintptr_t Ref2 = r6->mem->read<uintptr_t>(Ref1 + 0x40);
	this->address = r6->mem->read<uintptr_t>(Ref2 + 0x68);
}

bool ChatManager::is_open() {
	return r6->mem->read<bool>(this->address + 0xF7B);
}

void ChatManager::set_status(bool status) {
	r6->mem->write<bool>(this->address + 0xF7B, status);
	//1 Open
	//0 Closed
}

void ChatManager::set_message(std::string message) {
	//0x7F
	if (message.size() >= max_msg_size)
	{
		printf("You cant use strings that are longer than 0x7F\n");
		return;
	}
	r6->mem->write<int>(this->address + 0xED8, message.size());
	r6->mem->cwrite(this->address + 0xAD8, (void*)message.c_str(), message.size());
}

int ChatManager::get_type() {
	return r6->mem->read<int>(this->address + 0xF5C);
}
void ChatManager::set_type(int type) {
	r6->mem->write<int>(this->address + 0xF5C, type);
}

std::vector<ChatManager::Chat_log> ChatManager::log_messages() {
	std::vector<Chat_log>buffer;
	UINT16 array_size = r6->mem->read<UINT16>(this->address + 0x1020);
	uintptr_t log_array = r6->mem->read<uintptr_t>(this->address + 0x1018);
	for (UINT16 i = 0; i < array_size; i++) {

		Chat_log newlog;

		uintptr_t msg_ptr = r6->mem->read<uintptr_t>(log_array + i * 0x20);
		char msg[max_msg_size];
		for (int i = 0; i < max_msg_size; i++) {
			msg[i] = r6->mem->read<char>(msg_ptr + i);
			if (msg[i] == 0)
				break;
		}
		
		uintptr_t prefix_ptr = r6->mem->read<uintptr_t>(log_array + i * 0x20 + 8);
		char prefix[max_msg_size];
		for (int i = 0; i < max_msg_size; i++) {
			prefix[i] = r6->mem->read<char>(prefix_ptr + i);
			if (prefix[i] == 0)
				break;
		}
		newlog.Message = std::string(msg);
		newlog.Prefix = std::string(prefix);
		buffer.push_back(newlog);
	}
	return buffer;
}