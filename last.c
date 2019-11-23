#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

enum branch {CSE, EE, ME};

struct student {
    char rollno[MAX];
    char name[MAX];
    enum branch branch;
    int semester;
    int ncourses;
    char **course_codes;
};

struct instructor {
    char id[MAX];
    char name[MAX];
    int ncourses;
    char **courses_codes;
};

struct course {
    char code[MAX];
    char name[MAX];
    int credits;
    int ninstructors;
    char **instructor_ids;
    int nstudents;
    char **student_rollnos;
};

//----------------------------------------
struct student *students;
struct instructor *instructors;
struct course *courses;
//---------------------------------------
void load_records();
void load_students();
void load_instructors();
void load_courses();
//----------------------------------------
void print_students();
void print_student(struct student s);
void add_student(struct student s);
void addstudent(char *rollno, char *name,int b,int semester,int courses ,char** course_codes);
void deletestudent();
void modifystudent();
void printmodifystudent();
//-----------------------------------------
void print_instructors();
void print_instructor(struct instructor i);
void add_instructor(struct instructor i);
void addinstructor(char *id,char *name,int ncourses,char** course_codes);
void deleteinstructor();
void modifyinstructor();
void printmodifyinstructor();
//-----------------------------------
void print_courses();
void print_course(struct course c);
void add_course(struct course c);
void addcourse(char *code, char *name, int credits, int ninstructors, char **instructors_ids, int nstudents, char **student_rollnos);
void deletecourse();
void modifycourse();
void printmodifycourse();
//-----------------------------------

FILE *fps;
FILE *fpi;
FILE *fpc;
FILE *buffer;

char students_file[MAX] = "students.txt";
char courses_file[MAX] = "courses.txt";
char instructors_file[MAX] = "instructors.txt";

int ncourses = 0, nstudents = 0, ninstructors = 0;

int main() {
     int i,j;
     char rollno[MAX];
     char name[MAX];
     int b;
     int semester;
     char **course_codes;
     char id[MAX];
     char **courses_codes;
     char code[MAX];
     int credits;
     char **instructor_ids;
     char **student_rollnos;
     int m=0;
     int f=1;
    load_records();
	printf("Enter the number in which you want to perform changes:\n1.Students\n2.Instructors\n3.Courses\n>>>>>>");
	scanf("%d",&i);
	printf("Enter number for following steps:\n1.Display All\n2.Display\n3.Add\n4.Delete\n5.Modify\n>>>>>");
	scanf("%d",&j);
	if(i==1){
			switch(j){
					case 1:
				       		print_students();
				       		break;
                        case 2:					 
					 		printf("Enter Roll No.:");
        				 	scanf("%s",rollno);
    						for(int i=0;i<nstudents;i++){
    							if(strcmp(rollno,students[i].rollno)==0){
    									m++;
    							}
    							}
							if(m==0){
    							printf("\nEnter valid Roll no.\n");
    								exit(0);
								}                             		
								 else{ 
									for(int z=0;z<nstudents;z++){	
													if(strcmp(rollno,students[z].rollno)==0){		
                                 					print_student(students[z]);
                                 					exit(0);
                                        		}   
											}
                                    		}
                                        break;
                                case 3:
                                   	 	
											printf("Enter Roll No.:\n");
                                        scanf("%s",rollno);
                                        for(int i=0;i<nstudents;i++){
    										if(strcmp(rollno,students[i].rollno)==0){
    											printf("Student already exists.\n");
												f=0;
												break;
    										}
    									}
    									if(f==1){
    										printf("Enter name:\n");
											 scanf(" %[^\n]s",name);
                                        	printf("Enter Branch Code:\n");
											scanf("%d",&b);
                                         	printf("Enter Semester Number:\n");
											 scanf("%d",&semester);
                                         	int nco;
											 printf("Enter no.of courses enrolled:\n");
											 scanf("%d",&nco);
                                         	course_codes=malloc(nco*sizeof(char *));
                                        printf("Enter Course code:\n");
										for(int p=0;p<nco;p++){
                                         	course_codes[p]=malloc(MAX*sizeof(char));
											 scanf("%s",course_codes[p]);                                                                                  
                                        }
                                   		addstudent(rollno,name,b,semester,nco,course_codes);
                                   		int n=0;
										for (int l=0;l<ncourses;l++){
											for(int j=0;j<nco;j++){
												if(strcmp(courses[l].code,course_codes[j])==0){
													n++;
												}
										}
                                   		}
                                   		if(n==0){
                                   			printf("\nNeed to Enter Course Details.");
                                   		}
									    printf("Enter Code:");
					 					scanf("%s",code);
                                        for(int z=0;z<ncourses;z++){
    										if(strcmp(code,courses[z].code)==0){
    											printf("Code already exists.\n");
												f=0;
												break;
    										}
    									}
    									if(f==1){
											for(int i=0;i<ncourses;i++){
                                        	if(strcmp(code,courses[i].code)==0){
                                      		printf("\nCourse Already Exists.\n");
                                       		}          
											else{
                                        		printf("\nEnter Name:");
												scanf(" %[^\n]s",name);
												printf("\nEnter Credits:");
	                                        	scanf("%d",&credits);
	                                        	int ninstructors;
												printf("\nEnter No.of Instructors:");
        	                                	scanf("%d",&ninstructors);
        	                                	instructor_ids=malloc(ninstructors*sizeof(char *));
        	                                 	printf("\nEnter Instructor Ids':");
												 for(int i=0;i<ninstructors;i++){
        	                                 		instructor_ids[i]=malloc(MAX*sizeof(char));
        	                                 		
												 	scanf("%s",instructor_ids[i]);                                                                                  
        	                                	}
        	                           			   int nstudents; 
												   printf("\nEnter No.of Students:");
											   	scanf("%d",&nstudents);
												printf("\nEnter Students Rollnos':");
												for(int i=0;i<nstudents;i++){
        	                                 		student_rollnos[i]=malloc(MAX*sizeof(char));
        	                                 		scanf("%s",student_rollnos[i]);                                                                                  
        	                                	}  
        	                               		addcourse(code,name,credits,ninstructors,instructor_ids,nstudents,student_rollnos);
                                   			}
                                   		}
                                   	}
											}
										   break;
								  case 4:
                                	 			deletestudent();
                                 	 	   		break;
                               case 5:
                  						modifystudent();
                  						break; 
                  				default:
                  						printf("Enter Valid Number.\n");
										break;		  
				  }              		
                  }
	   if(i==2){
		        switch(j){
		        			case 1:
		        	       				print_instructors();
		        	       				break ;
		        				case 2:
		                				printf("Enter ID:\n");               	
                                        scanf("%s",id);
    									for(int z=0;z<ninstructors;z++){
    										if(strcmp(id,instructors[z].id)==0){
    											m++;
    										}
    									}
											if(m==0){
    											printf("Enter valid ID.\n");
    											exit(0);
											}                             		
										 else{
                                        for(int t=0;t<ninstructors;t++){
                                 			if(strcmp(id,instructors[t].id)==0){
                                 				print_instructor(instructors[t]);
                                        		exit(0);
											}          
                                        	}
                                        }
                                        break;
		        				case 3:
	                            	     printf("Enter ID:\n");
                                         scanf("%s",id);
                                        for(int z=0;z<ninstructors;z++){
    										if(strcmp(id,instructors[z].id)==0){
    											printf("Instructor already exists.\n");
												f=0;
												break;
    										}
    									}
    									if(f==1){
                                        		printf("Enter Name:\n");
												scanf(" %[^\n]s",name);
                                        		int nc;
												printf("Enter no.of Courses teaching:\n");
												scanf("%d",&nc);
                                        		courses_codes=malloc(ncourses*sizeof(char *));
                                                printf("Enter Course Code:\n");
												for(int z=0;z<nc;z++){
                                        			courses_codes[z]=malloc(MAX*sizeof(char));
													scanf("%s",courses_codes[z]);
												}
                                        		addinstructor(id,name,nc,courses_codes);		
											}
										break;
                                case 4:
                               				deleteinstructor();
                                        	break;
                                case 5:
										modifyinstructor();
                                        break;
								default:
                  						printf("\nEnter Valid Number.\n");
		}
	}
       if(i==3){
        		switch(j){
        						case 1:
        			      				print_courses();
        			      				break;
        		        		case 2:
        			      				printf("Enter Code:");
                                      	scanf("%s",code);
                                      	
    									for(int i=0;i<ncourses;i++){
    										if(strcmp(code,courses[i].code)==0){
    											m++;
    										}
    									}
											if(m==0){
    											printf("Enter valid Code.\n");
    											exit(0);
											}                             		
										 else{
                                      	for(int i=0;i<ncourses;i++){
                                      		if(strcmp(code,courses[i].code)==0){
                                      			print_course(courses[i]);
                                       	}          
                                       	}
                                       	}
                                      	break;
                                case 3:
										printf("Enter Code:");
					 					scanf("%s",code);
                                        for(int z=0;z<ncourses;z++){
    										if(strcmp(code,courses[z].code)==0){
    											printf("Code already exists.\n");
												f=0;
												break;
    										}
    									}
    									if(f==1){
											for(int i=0;i<ncourses;i++){
                                        	if(strcmp(code,courses[i].code)==0){
                                      		printf("\nCourse Already Exists.\n");
                                       		}          
											else{
                                        		printf("\nEnter Name:");
												scanf(" %[^\n]s",name);
												printf("\nEnter Credits:");
	                                        	scanf("%d",&credits);
	                                        	int ninstructors;
												printf("\nEnter No.of Instructors:");
        	                                	scanf("%d",&ninstructors);
        	                                	instructor_ids=malloc(ninstructors*sizeof(char *));
        	                                 	printf("\nEnter Instructor Ids':");
												 for(int i=0;i<ninstructors;i++){
        	                                 		instructor_ids[i]=malloc(MAX*sizeof(char));
        	                                 		
												 	scanf("%s",instructor_ids[i]);                                                                                  
        	                                	}
        	                           			   int nstudents; 
												   printf("\nEnter No.of Students:");
											   	scanf("%d",&nstudents);
												printf("\nEnter Students Rollnos':");
												for(int i=0;i<nstudents;i++){
        	                                 		student_rollnos[i]=malloc(MAX*sizeof(char));
        	                                 		scanf("%s",student_rollnos[i]);                                                                                  
        	                                	}  
        	                               		addcourse(code,name,credits,ninstructors,instructor_ids,nstudents,student_rollnos);
                                   			}
                                   		}
                                   	}
                                   		break;
                                case 4:
                                   	    deletecourse();
                                        break;
                                case 5:
										modifycourse();
                  						break; 		
                  				default:
                  						printf("\nEnter Valid Number.\n");
				}
	} 
return 0;
}
//-----------------------------------------------------------------------
void load_records() {
    load_students();
    load_instructors();
    load_courses();
}
//-----------------------------------------------------------------------
void load_students() {
    fps = fopen(students_file, "r");
    int nstudents;
    char buf[MAX];
    struct student s;
    fscanf(fps, "%d", &nstudents);
    for (int i=0; i<nstudents; i++) {
        fgets(buf, MAX, fps);
        fscanf(fps, "%s", s.rollno);
        fscanf(fps, " %[^\n]s", s.name);
        fscanf(fps, "%u", &s.branch);
        fscanf(fps, "%d", &s.semester);
        fscanf(fps, "%d", &s.ncourses);
        s.course_codes = malloc (s.ncourses * sizeof(char *));
        for (int j=0; j<s.ncourses; j++) {
            s.course_codes[j] = malloc (MAX * sizeof (char));
            fscanf(fps, "%s", s.course_codes[j]);
        }
        add_student(s);
    }
}

void load_instructors() {
    fpi = fopen(instructors_file, "r");
    int ninstructors;
    char buf[MAX];
    struct instructor i;
    fscanf(fpi, "%d", &ninstructors);
    for (int t=0; t<ninstructors; t++) {
        fgets(buf, MAX, fpi);
        fscanf(fpi, "%s", i.id);
        fscanf(fpi, " %[^\n]s", i.name);
        fscanf(fpi, "%d", &i.ncourses);
        i.courses_codes = malloc (i.ncourses * sizeof(char *));
        for (int j=0; j<i.ncourses; j++) {
            i.courses_codes[j] = malloc (MAX * sizeof (char));
            fscanf(fpi, "%s", i.courses_codes[j]);
        }
        add_instructor(i);
    }
}

void load_courses() {
    fpc = fopen(courses_file, "r");
    int ncourses;
    char buf[MAX];
    struct course c;
    fscanf(fpc, "%d", &ncourses);
    for (int i=0; i<ncourses; i++) {
        fgets(buf, MAX, fpc);
        fscanf(fpc, "%s", c.code);
        fscanf(fpc, " %[^\n]s", c.name);
        fscanf(fpc, "%d", &c.credits);
        fscanf(fpc, "%d", &c.ninstructors);
        c.instructor_ids = malloc (c.ninstructors * sizeof(char *));
        for (int j=0; j<c.ninstructors; j++) {
            c.instructor_ids[j] = malloc (MAX * sizeof (char));
            fscanf(fpc, "%s", c.instructor_ids[j]);
        }
        fscanf(fpc, "%d", &c.nstudents);
        c.student_rollnos = malloc (c.nstudents * sizeof(char *));
        for (int j=0; j<c.nstudents; j++) {
            c.student_rollnos[j] = malloc (MAX * sizeof (char));
            fscanf(fpc, "%s", c.student_rollnos[j]);
        }
        add_course(c);
    }
}

//---------------------STUDENTS--------------------------------------------
void print_students() {
    printf("Students' details\n-----------------\n");
          for (int i=0; i<nstudents; i++) {
       		print_student(students[i]);
    }
}

void print_student(struct student s) {
    printf("Roll no.: %s\n", s.rollno);
    printf("Name: %s\n", s.name);
    printf("Branch: %d\n", s.branch);
    printf("Semester: %d\n", s.semester);
    printf("List of courses: ");
    for (int i=0; i<s.ncourses; i++) {
        printf("%s ", s.course_codes[i]);
    }
    printf("\n");
	printf("\n");
}

void add_student(struct student s) {
    students = realloc (students, (nstudents+1)*sizeof(struct student));
    students[nstudents] = s;
    nstudents++;
}

void addstudent(char *rollno, char *name,int b,int semester,int courses ,  char** course_codes){
	buffer = fopen("Temp.txt","w");
	fps = fopen(students_file,"r");
	int c;
	fscanf(fps,"%d",&c);
	fprintf(buffer,"%d",c+1);
	char u;
	for(u=getc(fps);u!=EOF;u=getc(fps)){
		fputc(u , buffer);
	} 
	fputc('\n' , buffer);
	fprintf(buffer,"%s\n",rollno);
	fprintf(buffer,"%s\n",name);
	fprintf(buffer,"%d\n",b);
	fprintf(buffer,"%d\n",semester);
	fprintf(buffer,"%d\n",courses);
	for(int i=0;i<ncourses;i++){
		fprintf(buffer,"%s ",course_codes[i]);
	}
	fputc('\n' , buffer);
	fclose(buffer);
	fclose(fps);
	fps=fopen(students_file,"w");
	buffer=fopen("Temp.txt","r");
	char f;
	while((f=getc(buffer))!=EOF){
		fputc(f, fps);
	}
	fclose(buffer);
	fclose(fps);
	
	}

void deletestudent() {
	int m=0;
	char rollno[MAX];
	printf("Enter Roll No.:\n");
    scanf("%s",rollno);
	for(int i=0;i<nstudents;i++){
    	if(strcmp(rollno,students[i].rollno)==0){
    		m++;
    }
    }
    if(m==0){
    	printf("Enter valid Roll no.\n");
    		exit(0);
	}
		else{
			fps = fopen(students_file,"w");
    		fprintf(fps,"%d",nstudents-1);
			for(int i=0;i<nstudents;i++){
            	if(strcmp(rollno,students[i].rollno)!=0){
            		continue;
            	}
            	else{
            		fprintf(fps,"%s\n",students[i].rollno);
					fprintf(fps,"%s\n",students[i].name);
					fprintf(fps,"%d\n",students[i].branch);
					fprintf(fps,"%d\n",students[i].semester);
					fprintf(fps,"%d\n",students[i].ncourses);
					for(int j=0;j<ncourses;j++){
						fprintf(fps,"%s ",students[i].course_codes[j]);
					}
				fputc('\n' , fps);
				}
         }
	}
}

void modifystudent(){
	int m=0;
	char rollno[MAX];
	printf("Enter Roll No.:");   	    
    scanf("%s",rollno);
    for(int i=0;i<nstudents;i++){
    	if(strcmp(rollno,students[i].rollno)==0){
    		m++;
    	}
    }
    	if(m==0){
    		printf("Enter valid Roll no.\n");
    		exit(0);
		}
		else{
	for(int i=0;i<nstudents;i++){
		if(strcmp(rollno,students[i].rollno)==0){
            int u;
			printf("Enter which detail you want to modify:\n1.Roll No.\n2.Name\n3.Branch\n4.Semester\n5.No.of Courses\n>>>>>>\n");
			scanf("%d",&u);
			char mrollno[MAX];
			char mname[MAX];
			int mb;
			int msemester;
			int mncourses;
			char **mcourse_codes;
			switch(u){
				case 1:
					printf("Enter new Roll No.:\n");
					scanf("%s",mrollno);
					strcpy(students[i].rollno,mrollno);
					break;
				case 2:
					printf("Enter new Name:\n");
					scanf("%s",mname);
					strcpy(students[i].name,mname);
					break;
				case 3:
					printf("Enter new branch code:\n");
					scanf("%d",&mb);
					students[i].branch=mb;
					break;
				case 4:
					printf("Enter new Semester:\n");
					scanf("%d",&msemester);
					students[i].semester=msemester;
					break;
				case 5:
					printf("Enter new no.of courses:\n");
					scanf("%d",&mncourses);
					students[i].ncourses=mncourses;
					mcourse_codes=malloc(mncourses*sizeof(char *));
                            printf("Enter new Course Code (Press Enter for a new Course Code):\n");
							for(int z=0;z<mncourses;z++){
                            	mcourse_codes[z]=malloc(MAX*sizeof(char));
								scanf("%s",mcourse_codes[z]);
								strcpy(students[i].course_codes[z],mcourse_codes[z]);
							}
					break;
				default:
					printf("Enter valid Number.\n");
			       break;
			}
		}
	}
printmodifystudent();
}
}

void printmodifystudent(){
	fps=fopen(students_file,"w");
	fprintf(fps,"%d\n",nstudents);	
	fputc('\n',fps);
	for(int i=0;i<nstudents;i++){
		fprintf(fps,"%s\n",students[i].rollno);
		fprintf(fps,"%s\n",students[i].name);
		fprintf(fps,"%d\n",students[i].branch);
		fprintf(fps,"%d\n",students[i].semester);
		fprintf(fps,"%d\n",students[i].ncourses);
	for(int j=0;j<students[i].ncourses;j++){
		fprintf(fps,"%s ",students[i].course_codes[j]);
	}
	fputc('\n',fps);
	fputc('\n' , fps);
	}	
	fclose(fps);
}
//--------------------------------------END-------------------------------------------------------------

//--------------------------------------INSTRUCTORS-------------------------------------------------------------
void print_instructors() {
    printf("Instructors' details\n-----------------\n");
          for (int i=0; i<ninstructors; i++) {
        print_instructor(instructors[i]);
    }
}

void print_instructor(struct instructor i) {
    printf("Instructor ID: %s\n", i.id);
    printf("Name: %s\n", i.name);
    printf("Number of Courses: %d\n", i.ncourses);
    printf("List of courses: ");
    for (int t=0; t<i.ncourses; t++) {
        printf("%s ", i.courses_codes[t]);
    }
    printf("\n");
    printf("\n");
}

void add_instructor(struct instructor i) {
    instructors = realloc (instructors, (ninstructors+1)*sizeof(struct instructor));
    instructors[ninstructors] = i;
    ninstructors++;
}

void addinstructor(char *id, char *name,int ncourses , char** course_codes){
	buffer = fopen("Temp.txt","w");
	fpi = fopen(instructors_file,"r");
	int c;
	fscanf(fpi,"%d",&c);
	fprintf(buffer,"%d",c+1);
	char u;
	for(u=getc(fpi);u!=EOF;u=getc(fpi)){
		fputc(u , buffer);
	} 
	fputc('\n' , buffer);
	fprintf(buffer,"%s\n",id);
	fprintf(buffer,"%s\n",name);
	fprintf(buffer,"%d\n",ncourses);
	for(int j=0;j<ncourses;j++){
		fprintf(buffer,"%s ",course_codes[j]);
	}
	fputc('\n' , buffer);
	fclose(buffer);
	fclose(fpi);
	fpi=fopen(instructors_file,"w");
	buffer=fopen("Temp.txt","r");
	char f;
	while((f=getc(buffer))!=EOF){
		fputc(f, fpi);
	}
	fclose(buffer);
	fclose(fpi);
}

void deleteinstructor() {
	int m=0;
	char id[MAX];
	printf("Enter ID:\n");
    scanf("%s",id);
	for(int p=0;p<ninstructors;p++){
    	if(strcmp(id,instructors[p].id)==0){
    		m++;
    }
    }
    if(m==0){
    	printf("Enter valid Roll no.\n");
    		exit(0);
	}
		else{
			fpi = fopen(instructors_file,"w");
    		fprintf(fpi,"%d",ninstructors-1);
			for(int z=0;z<ninstructors;z++){
            	if(strcmp(id,instructors[z].id)!=0){
            		continue;
            	}
            	else{
            		fprintf(fpi,"%s\n",instructors[z].id);
					fprintf(fpi,"%s\n",instructors[z].name);
					fprintf(fpi,"%d\n",instructors[z].ncourses);
					for(int j=0;j<ncourses;j++){
						fprintf(fpi,"%s ",instructors[z].courses_codes[j]);
					}
				fputc('\n' , fpi);
				}
         }
	}
}

void modifyinstructor(){
	int m=0;
	char id[MAX];
	printf("Enter ID:"); 
	scanf("%s",id);
    for(int p=0;p<ninstructors;p++){
    	if(strcmp(id,instructors[p].id)==0){
    		m++;
    	}
    }
    	if(m==0){
    		printf("Enter valid ID.\n");
    		exit(0);
		}
		else{
	for(int p=0;p<ninstructors;p++){
		if(strcmp(id,instructors[p].id)==0){
            int u;
			printf("Enter which detail you want to modify:\n1.ID\n2.Name\n3.No.of Courses\n>>>>>>\n");
			scanf("%d",&u);
			char mid[MAX];
			char mname[MAX];
			int mncourses;
			char **mcourses_codes;
			switch(u){
				case 1:
					printf("Enter new ID.\n");
					scanf("%s",mid);
					strcpy(instructors[p].id,mid);
					break;
				case 2:
					printf("Enter new Name:\n");
					scanf("%s",mname);
					strcpy(instructors[p].name,mname);
					break;
				case 3:
					printf("Enter new no.of courses:\n");
					scanf("%d",&mncourses);
					instructors[p].ncourses=mncourses;
					mcourses_codes=malloc(mncourses*sizeof(char *));
                            printf("Enter new Course Code (Press Enter for a new Course Code):\n");
							for(int z=0;z<mncourses;z++){
                            	mcourses_codes[z] = malloc(MAX*sizeof(char));
								scanf("%s",mcourses_codes[z]);
								strcpy(instructors[p].courses_codes[z],mcourses_codes[z]);
								}
								break;
				default:
					printf("Enter valid Number.\n");
			       break;
			}
		}
	}
printmodifyinstructor();
}
}

void printmodifyinstructor(){
	fpi=fopen(instructors_file,"w");
	fprintf(fpi,"%d\n",ninstructors);
	fputc('\n',fpi);
	for(int k=0;k<ninstructors;k++){
		fprintf(fpi,"%s\n",instructors[k].id);
		fprintf(fpi,"%s\n",instructors[k].name);
		fprintf(fpi,"%d\n",instructors[k].ncourses);
	for(int j=0;k<instructors[k].ncourses;j++){
		fprintf(fpi,"%s ",instructors[k].courses_codes);
	}
	fputc('\n' , fpi);
	fputc('\n',fpi);
}
	fclose(fpi);
}
//--------------------------------------END-------------------------------------------------------------

//--------------------------------------COURSES----------------------------------------------------------

void print_courses() {
    printf("Courses details\n-----------------\n");
          for (int i=0; i<ncourses; i++) {
        print_course(courses[i]);
    }
}

void print_course(struct course c) {
    printf("Code: %s\n", c.code);
    printf("Name: %s\n", c.name);
    printf("Credits: %d\n", c.credits);
    printf("Number of Instructors: %d\n", c.ninstructors);
    for (int i=0; i<c.ninstructors; i++) {
        printf("%s ", c.instructor_ids[i]);
    }
	printf("Number of Students: %d\n", c.nstudents);
        for (int i=0; i<c.nstudents; i++) {
        printf("%s\t", c.student_rollnos[i]);
    }
    printf("\n");
    printf("\n");
}

void add_course(struct course c) {
    courses = realloc (courses, (ncourses+1)*sizeof(struct course));
    courses[ncourses] = c;
    ncourses++;
}

void addcourse(char *code, char *name, int credits , int ninstructors, char** instructor_ids, int nstudents, char **student_rollnos){
	buffer = fopen("Temp.txt","w");
	fpc = fopen(courses_file,"r");
	int c;
	fscanf(fpc,"%d",&c);
	fprintf(buffer,"%d",c+1);
	char u;
	for(u=getc(fpc);u!=EOF;u=getc(fpc)){
		fputc(u , buffer);
	} 
	fputc('\n' , buffer);
	fprintf(buffer,"%s\n",code);
	fprintf(buffer,"%s\n",name);
	fprintf(buffer,"%d\n",credits);
	fprintf(buffer,"%d\n",ninstructors);
	for(int j=0;j<ninstructors;j++){
		fprintf(buffer,"%s ",instructor_ids[j]);
	}
	fprintf(buffer,"%d\n",nstudents);
	for(int j=0;j<nstudents;j++){
		fprintf(buffer,"%s ",student_rollnos[j]);
	}
	fputc('\n' , buffer);
	fclose(buffer);
	fclose(fpc);
	fpc=fopen(students_file,"w");
	buffer=fopen("Temp.txt","r");
	char f;
	while((f=getc(buffer))!=EOF){
		fputc(f, fpc);
	}
	fclose(buffer);
	fclose(fpc);
}

void deletecourse() {
	int m=0;
	char code[MAX];
	printf("Enter Code:\n");
    scanf("%s",code);
	for(int i=0;i<ncourses;i++){
    	if(strcmp(code,courses[i].code)==0){
    		m++;
    }
    }
    if(m==0){
    	printf("Enter valid Roll no.\n");
    		exit(0);
	}
		else{
			fpc = fopen(courses_file,"w");
    		fprintf(fpc,"%d",ncourses-1);
			for(int i=0;i<ncourses;i++){
            	if(strcmp(code,courses[i].code)!=0){
            		continue;
            	}
            	else{
            		fprintf(fpc,"%s\n",courses[i].code);
					fprintf(fpc,"%s\n",courses[i].name);
					fprintf(fpc,"%d\n",courses[i].credits);
					fprintf(fpc,"%d\n",courses[i].ninstructors);
					for(int j=0;j<ninstructors;j++){
						fprintf(fpc,"%s ",courses[i].instructor_ids);
					}
					fprintf(fpc,"%d\n",courses[i].nstudents);
					for(int j=0;j<nstudents;j++){
						fprintf(fpc,"%s ",courses[i].student_rollnos);
					}
				fputc('\n' , fpc);
				}
         }
	}
}

void modifycourse(){
	int m=0;
	char code[MAX];
	printf("Enter Code:");   	    
    scanf("%s",code);
    for(int i=0;i<ncourses;i++){
    	if(strcmp(code,courses[i].code)==0){
    		m++;
    	}
    }
    	if(m==0){
    		printf("Enter valid Code.\n");
		}
		else{
	for(int i=0;i<ncourses;i++){
		if(strcmp(code,courses[i].code)==0){
            int u;
			printf("Enter which detail you want to modify:\n1.Code\n2.Name\n3.Credits\n4.No.of Instructors\n5.No.of Students\n>>>>>>\n");
			scanf("%d",&u);
			switch(u){
			char mcode[MAX];
			char mname[MAX];
			int mcredits;
			char **mcourses_codes;
			int  mninstructors;
			char **minstructor_ids;
			int mnstudents;
			char **mstudent_rollnos;
				case 1:
					printf("Enter new Code:\n");
					scanf("%s",mcode);
					strcpy(courses[i].code,mcode);
					break;
				case 2:
					printf("Enter new Name:\n");
					scanf(" %[^\n]s",mname);
					strcpy(courses[i].name,mname);
					break;
				case 3:
					printf("Enter new Credits:\n");
					scanf("%d",&mcredits);
					courses[i].credits=mcredits;
					break;
				case 4:
					printf("Enter new no.of instructors:\n");
					scanf("%d",&mninstructors);
					courses[i].ninstructors=mninstructors;
					minstructor_ids=malloc(mninstructors*sizeof(char *));
						printf("\nEnter new Instructor Id (Press Enter for a new ID):");
						for(int z=0;z<mninstructors;z++){
                            	minstructor_ids[z]=malloc(MAX*sizeof(char));
                                
								scanf("%s",minstructor_ids[z]);
								strcpy(courses[i].instructor_ids[z],minstructor_ids[z]);
							}
							break;
				case 5:
					printf("Enter new no.of students:\n");
					scanf("%d",&mnstudents);
					mstudent_rollnos=malloc(mnstudents*sizeof(char *));
                            printf("\nEnter new Student Roll No. (Press Enter for a new Roll No.):");
							for(int z=0;z<mnstudents;z++){
                            	mstudent_rollnos[z]=malloc(MAX*sizeof(char));
								scanf("%s",mstudent_rollnos[z]);
								strcpy(courses[i].student_rollnos[z],mstudent_rollnos[z]);
								}
								break;
				default:
					printf("Enter valid Number.\n");
			       	break;
			}
		}
	}
printmodifycourse();

}
}

void printmodifycourse(){
	fpc=fopen(courses_file,"w");
	fprintf(fpc,"%d\n",ncourses);
	fputc('\n',fpc);
	for(int i=0;i<ncourses;i++){
		fprintf(fpc,"%s\n",courses[i].code);
		fprintf(fpc,"%s\n",courses[i].name);
		fprintf(fpc,"%d\n",courses[i].credits);
		fprintf(fpc,"%d\n",courses[i].ninstructors);
			for(int j=0;j<courses[i].ninstructors;j++){
				fprintf(fpc,"%s ",courses[i].instructor_ids[j]);
			}
			fputc('\n',fpc);
		fprintf(fpc,"%d\n",courses[i].nstudents);
			for(int j=0;j<courses[i].nstudents;j++){
				fprintf(fpc,"%s ",courses[i].student_rollnos[j]);
			}
	fputc('\n' , fpc);
	fputc('\n' , fpc);
	}
	fclose(fpc);
}
//----------------------------------------------END---------------------------------------------------------------
