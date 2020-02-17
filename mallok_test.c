
/*
 *TCSS 333
 *HW7
 *@Author: Yunhan Tu
 *@version 3/3/18
 */

#include "mallok.c"

void test1();
void test2();
void test3();
void test4();
void test5();
void customTest0();

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);

	test1();
	free_pool();
	test2();
	free_pool();
	test3();
	free_pool();
	test4();
	free_pool();
	test5();
	free_pool();

}

void test1() {
	int count = 0;
	create_pool(1000);
	printf("test 1 create_pool(%d)\n", 1000);
	while (my_malloc(10) != NULL) {
		++count;
	}
	printf("Final count %d \n", count);
}


void test2() {
	int i, k;
	void *ptr[5];
	create_pool(1000);
	printf("test 2create_pool(%d)\n", 1000);
	for (k = 1; k <= 5; k++) {
		printf("repeat = %d\n", k);
		for (i = 0; i < 5; i++) {
			ptr[i] = my_malloc(200);
			if (ptr[i] == 0x0)
				printf(" fail\n");
			else
				printf(" Success\n");
		}
		for (i = 0; i < 5; i++) {
			my_free(ptr[i]);
		
		}
	}
}


void test3() {
	int i;
	void *ptr[5], *ptr2 = NULL;
	create_pool(1000);
	printf("test 3 create_pool(%d)\n", 1000);
	for (i = 0; i < 5; i++) {
		ptr[i] = my_malloc(200);
		if (ptr[i] == 0x0)
			printf(" fail\n");
		else
			printf(" Success\n");
	}
	my_free(ptr[5 / 2]);

	 ptr2 = my_malloc(210);
	printf("my_malloc(210):  %s\n", 
			ptr2 != NULL ? "Success" : "fail");

	ptr2 = my_malloc(150);
	printf("my_malloc(150):  %s\n", 
			ptr2 != NULL ? "Success" : "fail");
	
	ptr2 = my_malloc(60);
	printf("my_malloc(60):  %s\n",
			ptr2 != NULL ? "Success" : "fail");
	
	ptr2 = my_malloc(50);
	printf("my_malloc(50):  %s\n", 
			ptr2 != NULL ? "Success" : "fail");
	
	
}

void test4() {
	int i, k;
	char c, *chPtr;
	void *ptr[5];
	create_pool(1000);
	printf("test 4 create_pool(%d)\n", 1000);
	
	for (i = 0; i < 5; i++) {
		ptr[i] = my_malloc(200);
		c = i + 65; 
		memset(ptr[i], c, 200);
	}
	for (i = 0; i < 5; i++) {
	
		for (chPtr = (char*) ptr[i], k = 0; chPtr < (char*) ptr[i] + 200;
				chPtr++, k++) {
			if (k < 20) 
				printf("%c ", *chPtr); 
			else {
				printf("\n%c ", *chPtr);
				k = 0;
			}
		}
		printf("\n");
	}
}


void test5() {
	int i;
	void *ptr = NULL, *ptr2[4], *ptr3[10];
	create_pool(1000);
	printf("create_pool(%d)\n", 1000);

	printf("\nmy_malloc(1000):\n");
	ptr = my_malloc(1000);
	printf("my_malloc(1000):%p\n", ptr); 
	my_free(ptr);

	printf("\nmy_malloc(250):\n");
	for (i = 0; i < 4; i++) {
		ptr2[i] = my_malloc(250);
		printf("my_malloc(250):%p\n", ptr2[i]);
	}
	for (i = 0; i < 4; i++)
		my_free(ptr2[i]);

	printf("\nmy_malloc(100):\n");
	for(i = 0; i < 10; i++) {
		ptr3[i] = my_malloc(100);
		printf("my_malloc(100):%p\n", ptr3[i]);
	}
	for (i = 0; i < 10; i++)
			my_free(ptr3[i]);


}
