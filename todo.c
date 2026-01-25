#include <stdio.h>

FILE *open_file(void){
//open task list
	FILE *todo = fopen("todo.txt","r+"); //open/create todo.txt for read and append
        if (todo == NULL){
                perror("fopen"); //print error if file was not opened/created
                return NULL;
        }
	return todo;
}


int save_task(FILE *todo){
//function saves new task into todo.txt
	char task[61]; //61 is a buffer
	printf("Type a new task:");
        
	if(fgets(task, sizeof(task), stdin) == NULL){
		return 0; //exit 
	}
	
	else{
        	if (fseek(todo, 0, SEEK_END) != 0) return 0;
		fprintf(todo,"[ ]  %s",task);
	}
	return -1;
}

int view_tasklist(FILE *todo){
//function displays todo list
	int count = 1;
	char line[1024];
	rewind(todo); //moves cursor to the beginning of the file
	
	while (fgets(line, sizeof(line), todo)) {
    		printf("%d. %s", count, line);
		count += 1;
	}

	return -1;
}


void overwrite_task_state(FILE *todo,char task_no,char new_state){
	//move to task no.
	printf("%d",task_no);	
	fputc(new_state, todo);//chagnes the state of the task
	fflush(todo); //forces change to happen now
	}

int complete_task(FILE *todo){
	char target[2];
	
	view_tasklist(todo);
	printf("========================\n");
	printf("Which task would you like to complete?\n");
	
	if(fgets(target,sizeof(target),stdin) == NULL){
		return 0;
	}
	
	overwrite_task_state(todo,target[0],'X');	
	
	return -1;
	}

void clear_screen(void) {
    printf("\033[2J\033[H"); // clear screen + move cursor home
    fflush(stdout);
}

int clear_tasklist(FILE **todo){
	//close and reopens file to wipe it
	char input [16]; 
	printf("\033[31mAre you sure you want to clear tasklist? This step cannot be undone.\033[0m\n");
	printf("Y/N\n");

	if(fgets(input,sizeof(input),stdin) == NULL){
                return 0;
        }

	else if (input[0] == 'Y' || input[0] == 'y'){
		*todo = freopen("todo.txt","w+",*todo);
		if (!*todo){perror("freopen"); return 1;}
		printf("Tasklist was successfully cleared\n");
		}
	
	else if (input[0] == 'N' || input[0] == 'n'){
		printf("Task list was not cleared\n");
		}
	
	else{
		printf("\033[31minvalid input tasklist was not cleared\033[0m\n");
		return -1;
		}

	return -1;
}

void display_menu(void){
//display menu items to user 
	printf("========================\n");
        printf("===Todo list============\n");
        printf("What would you like to do today?\n");
        printf("[1] Add a new task\n");
        printf("[2] Complete a task\n");
        printf("[3] Delete a task\n");
        printf("[4] View tasklist\n");
	printf("[5] Clear tasklist\n");
        printf("[0] Quit\n");
        printf("========================\n");
        printf("Please enter a number:");
        printf("> ");

}

int select_menu(char user_input, FILE* todo){
//user selects menu item
	switch(user_input){
        	case '1': printf("add a new task\n"); save_task(todo);break;
                case '2': printf("complete a task\n");break;
                case '3': printf("delete a task\n");break;
                case '4': view_tasklist(todo);break;
		case '5': clear_tasklist(&todo); break;
                case '0': return 0; 
                default: printf("Invalid choice. \n"); break; //User may input non-valid integers
                }
	return 1;
}

int main(void){
	
	//open up todo.txt 
	FILE *todo = open_file();	
	if (!todo) return 1; //file fails to load 

	char user_input[16];//hold at most 15 characters
	int state = -1;

	while (1){
		display_menu();	
		if(fgets(user_input,sizeof user_input,stdin)==NULL) return 0;
		char c = user_input[0];
		
		//reject if len(user_input) > 1 char
		if (user_input[1]!='\n'){
			printf("Please enter 1 character only.\n");
			continue;
		} 
		else if (c >= '0' && c <= '9'){
			clear_screen();
			state=select_menu(c,todo); 
			if (state==0){ fclose(todo); return 0;} //close file and end programme	
		}
		else{ 
			printf("Please enter a number from 1-9.\n");
		}
	}
	return 0;
}
