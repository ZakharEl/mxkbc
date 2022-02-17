#include <string>
#include <sys/socket.h> //socket, AF_UNIX, SOCK_STREAM
#include <sys/un.h> //struct sockaddr_un
#include <unistd.h> //write
#include <getopt.h> //getopt_long, required_argument
#include <sstream>
#include <string.h> //strcmp
#include <iostream> //getline, cin

//stands for modular X key bind client

std::string sockpath = std::string(getenv("HOME")) + "/.config/mxkbd/mxkbd.socket"; //location of the socket file
std::string socket_string("");
struct sockaddr_un sock_struct;
int sock_fd;
int argc;
char **argv;

void write_to_socket(std::string write_string) {
	if(write(sock_fd, write_string.c_str(), write_string.length()) < 0) {
		exit(-1);
	}
}

void build_up_socket_string(std::string string_to_add) {
	socket_string += std::to_string(string_to_add.length()) + " " + string_to_add;
}

bool is_option_argv(std::string option) {
	if(optind >= argc) {
		return false;
	}
	std::string string_to_check = argv[optind]; 
	if(string_to_check.compare(option) == 0) {
		optind++;
		return true;
	}
	return false;
}

bool add_operation() {
	if(!(is_option_argv(std::string("a")) || is_option_argv(std::string("add")))) {
		return false;
	}
	build_up_socket_string(std::string("a"));
	if(is_option_argv(std::string("m")) || is_option_argv(std::string("mode"))) {
		build_up_socket_string(std::string("m"));
		if(optind >= argc) {
			exit(-1);
		}
		build_up_socket_string(std::string(argv[optind]));
		optind++;
		if(optind < argc) {
			build_up_socket_string(std::string(argv[optind]));
		}
	}
	else if(is_option_argv(std::string("k")) || is_option_argv(std::string("keybind"))) {
		build_up_socket_string(std::string("k"));
		if(optind >= argc) {
			exit(-1);
		}
		if(is_option_argv(std::string("-g")) || is_option_argv(std::string("-s")) || is_option_argv(std::string("-d"))) {
			build_up_socket_string(std::string(argv[optind-1]));
		}
		else if(is_option_argv(std::string("-m"))) {
			build_up_socket_string(std::string("-m"));
			if(optind >= argc) {
				exit(-1);
			}
			build_up_socket_string(std::string(argv[optind]));
			optind++;
		}
		if(optind >= argc-1) {
			exit(-1);
		}
		build_up_socket_string(std::string(argv[optind]));
		optind++;
		if(is_option_argv(std::string("-"))) {
			std::string command;
			getline(std::cin, command, {});
			build_up_socket_string(command);
		}
		else {
			build_up_socket_string(std::string(argv[optind]));
			optind++;
		}
		if(optind < argc) {
			build_up_socket_string(std::string(argv[optind]));
		}
	}
	else {
		exit(-1);
	}
	return true;
}

bool set_operation() {
	if(!(is_option_argv(std::string("s")) || is_option_argv(std::string("set")))) {
		return false;
	}
	build_up_socket_string(std::string("s"));
	if(is_option_argv(std::string("-g")) || is_option_argv(std::string("-s")) || is_option_argv(std::string("-d"))) {
		build_up_socket_string(std::string(argv[optind-1]));
		goto set_mode_member;
	}
	else if(is_option_argv(std::string("m")) || is_option_argv(std::string("mode"))) {
		build_up_socket_string(std::string("m"));
		if(optind >= argc) {
			exit(-1);
		}
		build_up_socket_string(std::string(argv[optind]));
		optind++;
		set_mode_member:
			if(is_option_argv(std::string("-g")) || is_option_argv(std::string("-s")) || is_option_argv(std::string("-d"))) {
				build_up_socket_string(std::string(argv[optind-1]));
				return true;
			}
			else if(is_option_argv(std::string("n")) || is_option_argv(std::string("name"))) {
				build_up_socket_string(std::string("n"));
			}
			else if(is_option_argv(std::string("d")) || is_option_argv(std::string("description"))) {
				build_up_socket_string(std::string("d"));
			}
			else {
				exit(-1);
			}
			if(optind >= argc) {
				exit(-1);
			}
			build_up_socket_string(std::string(argv[optind]));
	}	
	else if(is_option_argv(std::string("k")) || is_option_argv(std::string("keybind"))) {
		build_up_socket_string(std::string("k"));
		if(optind >= argc) {
			exit(-1);
		}
		if(is_option_argv(std::string("-g")) || is_option_argv(std::string("-s")) || is_option_argv(std::string("-d"))) {
			build_up_socket_string(std::string(argv[optind-1]));
		}
		else if(is_option_argv(std::string("-m"))) {
			build_up_socket_string(std::string("-m"));
			if(optind >= argc) {
				exit(-1);
			}
			build_up_socket_string(std::string(argv[optind]));
			optind++;
		}
		if(optind >= argc) {
			exit(-1);
		}
		build_up_socket_string(std::string(argv[optind]));
		if(is_option_argv(std::string("s")) || is_option_argv(std::string("seq"))) {
			build_up_socket_string(std::string("s"));
		}
		else if(is_option_argv(std::string("d")) || is_option_argv(std::string("description"))) {
			build_up_socket_string(std::string("d"));
		}
		else if(is_option_argv(std::string("c")) || is_option_argv(std::string("command"))) {
			build_up_socket_string(std::string("c"));
		}
		else {
			exit(-1);
		}
		if(optind >= argc) {
			exit(-1);
		}
		build_up_socket_string(std::string(argv[optind]));
	}
	else {
		exit(-1);
	}
	return true;
}

bool remove_operation() {
	if(!(is_option_argv(std::string("r")) || is_option_argv(std::string("remove")))) {
		return false;
	}
	build_up_socket_string(std::string("r"));
	if(is_option_argv(std::string("-g")) || is_option_argv(std::string("-s")) || is_option_argv(std::string("-d"))) {
		build_up_socket_string(std::string(argv[optind-1]));
	}
	else if(is_option_argv(std::string("m")) || is_option_argv(std::string("mode"))) {
		build_up_socket_string(std::string("m"));
		if(optind >= argc) {
			exit(-1);
		}
		build_up_socket_string(std::string(argv[optind]));
		optind++;
	}	
	else if(is_option_argv(std::string("k")) || is_option_argv(std::string("keybind"))) {
		build_up_socket_string(std::string("k"));
		if(optind >= argc) {
			exit(-1);
		}
		if(is_option_argv(std::string("-g")) || is_option_argv(std::string("-s")) || is_option_argv(std::string("-d"))) {
			build_up_socket_string(std::string(argv[optind-1]));
		}
		else if(is_option_argv(std::string("-m"))) {
			build_up_socket_string(std::string("-m"));
			if(optind >= argc) {
				exit(-1);
			}
			build_up_socket_string(std::string(argv[optind]));
			optind++;
		}
		if(optind >= argc) {
			exit(-1);
		}
		build_up_socket_string(std::string(argv[optind]));
	}
	else {
		exit(-1);
	}
	return true;
}

bool list_operation() {
	if(!(is_option_argv(std::string("l")) || is_option_argv(std::string("list")))) {
		return false;
	}
	build_up_socket_string(std::string("l"));
	if(is_option_argv(std::string("m")) || is_option_argv(std::string("mode"))) {
		build_up_socket_string(std::string("m"));
			if(optind >= argc) {
				exit(-1);
			}
			build_up_socket_string(std::string(argv[optind]));
			optind++;
			goto list_mode_prop;
	}
	else if(is_option_argv(std::string("-g")) || is_option_argv(std::string("-s")) || is_option_argv(std::string("-d")) || is_option_argv(std::string("-a"))) {
		build_up_socket_string(std::string(argv[optind-1]));
		list_mode_prop:
			if(optind == argc) {
				return true;
			}
			else {
				if(is_option_argv(std::string("d")) || is_option_argv(std::string("description"))) {
					build_up_socket_string(std::string("d"));
				}
				else {
					exit(-1);
				}
			}
	}
	else if(is_option_argv(std::string("k")) || is_option_argv(std::string("keybind"))) {
		build_up_socket_string(std::string("k"));
		if(is_option_argv(std::string("-g")) || is_option_argv(std::string("-s")) || is_option_argv(std::string("-d"))) {
			build_up_socket_string(std::string(argv[optind-1]));
		}
		else if(is_option_argv(std::string("-m"))) {
			build_up_socket_string(std::string("-m"));
			if(optind >= argc) {
				exit(-1);
			}
			build_up_socket_string(std::string(argv[optind]));
			optind++;
		}
		if(is_option_argv(std::string("-a"))) {
			build_up_socket_string(std::string("-a"));
			if(optind == argc) {
				return true;
			}
		}
		else {
			build_up_socket_string(std::string(argv[optind]));
			optind++;
		}
		if(is_option_argv(std::string("d")) || is_option_argv(std::string("description"))) {
			build_up_socket_string(std::string("d"));
		}
		else if(is_option_argv(std::string("c")) || is_option_argv(std::string("command"))) {
			build_up_socket_string(std::string("c"));
		}
		else {
			exit(-1);
		}
	}
	return true;
}

std::stringstream read_from_socket() {
	char dataPtr[32768] = {};
	std::string contents = "";
	if(read(sock_fd, dataPtr, 32767) < 0) {
		exit(-1);
	}
	contents += dataPtr;
	return std::stringstream(contents);
}

bool parse_server_message(std::stringstream &p, std::string &r) {
	int length_to_read = 0;
	p >> length_to_read;
	if(p.eof()) {
		return false;
	}
	char *buf = new char [length_to_read + 1]();
	p.ignore();
	p.read(buf, length_to_read);
	if(p.eof()) {
		delete[] buf;
		return false;
	}
	r = buf;
	delete[] buf;
	return true;
}

int main(int largc, char *largv[]) {
	argc  =  largc;
	argv  =  largv;
	if(is_option_argv(std::string("-s"))) {
		if(optind < argc) {
			sockpath = argv[optind];
			optind++;
		}
	}
	if(!(add_operation() || remove_operation() || set_operation() || list_operation ())) {
		exit(-1);
	}
	sock_fd = socket(AF_UNIX, SOCK_SEQPACKET, 0);
	sock_struct.sun_family = AF_UNIX;
	strcpy(sock_struct.sun_path, sockpath.c_str());
	if(connect(sock_fd, (struct sockaddr *) &sock_struct, sizeof(struct sockaddr_un)) == -1) {
		exit(-1);
	}
	write_to_socket(socket_string);
	std::stringstream server_response = read_from_socket();
	std::string server_response_portion = "";
	if(parse_server_message(server_response, server_response_portion)) {
		if(server_response_portion.compare(std::string("ok")) == 0) {
			while(parse_server_message(server_response, server_response_portion)) {
				printf("%s\n", server_response_portion.c_str());
			}
		}
		else if(server_response_portion.compare(std::string("err")) == 0) {
			parse_server_message(server_response, server_response_portion);
			dprintf(2, "%s\n", server_response_portion.c_str());
			exit(-1);
		}
		else {
			dprintf(2, "server does not indicate success or failure");
			exit(-1);
		}
	}
	else {
		dprintf(2, "no response from server");
		exit(-1);
	}
	close(sock_fd);
	return 0;
}
