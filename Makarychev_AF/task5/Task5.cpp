#include <iostream>
#include <string>
#include <map>
#include <vector>

using std::string;
using std::vector;
using std::map;

const std::vector<int> DENOMINATIONS = { 5000, 2000, 1000, 500, 200, 100 };
const int CASSETTE_CAPACITY = 2000;          
const int INITIAL_LOAD_PERCENT = 80;         
const int MAX_NOTES_PER_OPERATION = 40;

bool is_number(const string& s);

class client {
	private:
		string name;
		string num_card;
		string Pin;
		unsigned int money;
		bool stat;
	public:
		client(string s = "-", string a = "0001", string b = "0000", int m = 0) {
			name = s;
			num_card=a;
			Pin = b;
			money = m;
			stat = true;
		}
		string& get_pin() {
			return Pin;
		}
		void block() {
			stat = false;
		}
		unsigned int balance() {
			return money;
		}
		void setBalance(unsigned int t) {
			money = t;
		}
		bool is_blocked() {
			return stat;
		}
};

class ProcessingCenter {
	private:
		map<string,client> data;
		client err;
	public:
		bool addClient(const string& cardNumber, const string& fullName, int balance, const string& pin) {
			if (data.find(cardNumber) != data.end()) {
				return false;
			}
			if (cardNumber.length() != 4 || !(is_number(cardNumber))) {
				return false;
			}
			if (pin.length() != 4 || !(is_number(pin))) {
				return false;
			}
			data.emplace(cardNumber,(cardNumber, fullName, balance, pin));
			return true;
		}
		client& find_client(const string& card)  {
			auto it = data.find(card);
			return (it != data.end()) ? it->second : err;
		}
		bool check_pin(const string& card, const string& pin) {
			client t = find_client(card);
			if (t.get_pin() == pin) {
				return true;
			}
			return false;
		}
		void block(const string& card) {
			client t = find_client(card);
			t.block();
		}
		unsigned int balance(const string& card) {
			client temp = find_client(card);
			return temp.balance();
		}
		void set_balance(const string& card, int del) {
			client temp = find_client(card);
			temp.setBalance(temp.balance() + del);
		}
		bool is_blocked(const string& card){
			client temp = find_client(card);
			return temp.is_blocked();
		}
};

class ATM {
	private:
		ProcessingCenter& pc;
		map <int, int> cass;
		string card;
		bool authentication;
		int err;
	public:
		ATM(ProcessingCenter& center) :pc(center), authentication(false), err(0) {
			int initialCount = CASSETTE_CAPACITY * INITIAL_LOAD_PERCENT / 100;
			for (int denom : DENOMINATIONS)
				cass[denom] = initialCount;
		}
		void Getcard(const string& Card) {
			if (is_number(Card) && Card.length() == 4) {
				card = Card;
			}
		}

};

bool is_number(const string& s){
	return !s.empty() && (s.find_first_not_of("0123456789") == s.npos);
}
