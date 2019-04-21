//trylock/main.cpp
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

struct MyStr
{
	int flag = 0;
	static pthread_mutex_t mutex;
};

pthread_mutex_t MyStr::mutex;

void* foo1(void* arg){
	std::cout << "\nfoo1 thread has started...\n";
	int rc;

	int* flg = (int*) &(((MyStr*)arg)->flag);
	while(*flg == 0)
	{
		if ((rc = pthread_mutex_trylock(&MyStr::mutex) != 0)){
				std::cout << "\nfoo1: " << strerror(rc) << "\n";
		}else {
			std::cout << "mutex lock by 1\n";

			for (int i = 0; i < 5; ++i)
			{
				std::cout << "1";
				fflush(stdout);
				sleep(1);
			}

			if ((rc = pthread_mutex_unlock(&MyStr::mutex)) != 0){
				std::cout << strerror(rc);
				return (void*) 8;
			}

			std::cout << "\nmutex unlock by foo1\n";

		}

		sleep(1);

	}

	std::cout << "foo1 thread has finished...\n";

	return 0;
}

void* foo2(void* arg){
	std::cout << "\nfoo2 thread has started...\n";
	int rc;

	int* flg = (int*) &(((MyStr*)arg)->flag);
	while(*flg == 0)
	{
		if ((rc = pthread_mutex_trylock(&MyStr::mutex)) != 0){
				std::cout << "\nfoo2: " << strerror(rc) << "\n";
		}else{
			std::cout << "mutex lock by 2\n";

			for (int i = 0; i < 5; ++i)
			{
				std::cout << "2";
				fflush(stdout);
				sleep(1);
			}

			if ((rc = pthread_mutex_unlock(&MyStr::mutex)) != 0){
				std::cout << strerror(rc);
				return (void*) 10;
			}

			std::cout << "\nmutex unlock by foo2\n";
		}

		sleep(1);

	}

	std::cout << "foo2 thread has finished...\n";

	return 0;
}

int main(int argc, char const *argv[])
{
	std::cout << "Main thread has started...\n";

	pthread_t id_1;
	pthread_t id_2;
	MyStr str1, str2;
	int rc;

	if ((rc = pthread_mutex_init(&MyStr::mutex, NULL)) != 0){
		strerror(rc);
		return 1;
	}

	if ((rc = pthread_create(&id_1, NULL, foo1, &str1)) != 0){
		strerror(rc);
		return 2;
	}

	if ((rc = pthread_create(&id_2, NULL, foo2, &str2)) != 0){
		strerror(rc);
		return 3;
	}

	getchar();
	
	str1.flag = str2.flag = 1;

	if ((rc = pthread_join(id_1, NULL)) != 0){
		strerror(rc);
		return 4;
	}

	if ((rc = pthread_join(id_2, NULL)) != 0){
		strerror(rc);
		return 5;
	}

	if ((rc = pthread_mutex_destroy(&MyStr::mutex)) != 0){
		strerror(rc);
		return 6;
	}

	std::cout << "Main thread has finished...\n";

	return 0;
}
