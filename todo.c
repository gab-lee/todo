#include <stdio.h>

void save_task(FILE *todo){

	char task[61]; //61 is a buffer
	printf("Type a new task:\n");
        fgets(task, sizeof task, stdin);
        fprintf(todo,"%s",task);

}

int main(void){
	//open task list
	FILE *todo = fopen("todo.txt","w"); //open/create todo.txt for writing
        if (todo == NULL){
                perror("fopen"); //print error if file was not opened/created
                return 1;
        }


	int choice = 0;

	while (1){
		printf("===Todo list============");
		printf("\nWhat would you like to do today?\n");
		printf("[1] Add a new task\n");
		printf("[2] Complete a task\n");
		printf("[3] Delete a task\n");
		printf("[4] View tasklist\n");
		printf("[0] Quit\n");
		printf("========================\n");
		printf("Please enter a number:");
		printf("> ");
	
	
		if (scanf("%d",&choice)!=1){
			//reject because input wasn't a number
			printf("Please enter a number\n");
			continue;
		}

		switch(choice){
			case 1: printf("add a new task\n"); save_task(todo);break;
			case 2: printf("complete a task\n");break;
			case 3: printf("delete a task\n");break;
			case 4: printf("tasklist\n");break;
			case 0: fclose(todo); return 0; //Ends main() 
			default: printf("Invalid choice. \n"); break; //User may input non-valid integers

		}
	}
	return 0;
}
