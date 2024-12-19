//
//  main.c
//  Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define EXERCISEFILEPATH "exercises.txt"
#define DIETFILEPATH "diets.txt"
#define HEALTHFILEPATH "health_data.txt"

static int choice;

int main() {
	// To initialize the health data object
    HealthData health_data = {0};
    
    // Tocode: to read the list of the exercises and diets
    FILE *exercises_file = fopen(EXERCISEFILEPATH,"r"); //exercises���� �о���� 
    FILE *diets_file = fopen(DIETFILEPATH,"r"); //diets ���� �о���� 
    if (exercises_file == NULL) {
    printf("Error .\n");
    return 1;
}
     loadExercises(exercises_file);
     loadDiets(diets_file);
     
     fclose(exercises_file);
     fclose(diets_file);

    // ToCode: to run the "Healthcare Management Systems" until all calories are used up or the user wants to exit the system
    //���� Į�θ��� ����ϱ�
    
	int calculateRemainingCalories(const HealthData* health_data){
		int totalCaloriesConsumed = health_data->total_calories_intake; //���ü�����Į�θ�
		int totalCaloriesBurned = health_data->total_calories_burned; //���� ����� �Ҹ��� Į�θ�
		int basalMetabolicRate = BASAL_METABOLIC_RATE; //���� ��緮 �Ҹ�Ǵ� Į�θ�
		int netCalories = totalCaloriesConsumed - totalCaloriesBurned - basalMetabolicRate ; //������ ���� ����Į�θ�
		int remainingCalories = DAILY_CALORIE_GOAL - netCalories;
		
		return remainingCalories;
	} 
	
	do {
    	//���� Į�θ��� 0���ϸ� ���α׷��� �����Ѵ�
    	int remainingCalories = calculateRemainingCalories(&health_data);
		if (remainingCalories <=0) {
            printf("You have consumed all your calories for today! \n");
		} 
		else{
			printf("\n=======================================================================\n");
        	printf("[Healthcare Management Systems] \n");
        	printf("1. Exercise \n");
        	printf("2. Diet \n");
        	printf("3. Show logged information \n");
        	printf("4. Exit \n");
        	printf("Select the desired number: ");
        	scanf("%d", &choice);
        	printf("=======================================================================\n");
        }
        
		// ToCode: to run the sysmtem based on the user's choice
        switch (choice) {
            case 1:
            	 //��Է� 
                break;
                
            case 2:
            	inputDiet(&health_data); //�Ĵ��Է� 
            	
                break;
                
            case 3:
            	printHealthData(&health_data); // �ǰ���������� 
                break;
                
            case 4:
            	
    			printf("Exit the system.\n");
    			printf("=======================================================================\n");
                break;
                
            default:
                printf("[Error] Invalid option. \n");
                printf("Please try again! \n");
        }
          // ���� ������ health_data.txt ���Ͽ� ���
        FILE *health_file = fopen(HEALTHFILEPATH, "w");
        if (health_file != NULL) {
            saveData(health_file, &health_data);
            fclose(health_file);
        } else {
            printf("Error: Unable to backup health data.\n");
        }
    } while (choice!= 4 && calculateRemainingCalories(&health_data) > 0); 

    return 0; 
}

