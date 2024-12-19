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
    FILE *exercises_file = fopen(EXERCISEFILEPATH,"r"); //exercises파일 읽어오기 
    FILE *diets_file = fopen(DIETFILEPATH,"r"); //diets 파일 읽어오기 
    if (exercises_file == NULL) {
    printf("Error .\n");
    return 1;
}
     loadExercises(exercises_file);
     loadDiets(diets_file);
     
     fclose(exercises_file);
     fclose(diets_file);

    // ToCode: to run the "Healthcare Management Systems" until all calories are used up or the user wants to exit the system
    //남은 칼로리를 계산하기
    
	int calculateRemainingCalories(const HealthData* health_data){
		int totalCaloriesConsumed = health_data->total_calories_intake; //오늘섭취한칼로리
		int totalCaloriesBurned = health_data->total_calories_burned; //오늘 운동으로 소모한 칼로리
		int basalMetabolicRate = BASAL_METABOLIC_RATE; //기초 대사량 소모되는 칼로리
		int netCalories = totalCaloriesConsumed - totalCaloriesBurned - basalMetabolicRate ; //실제로 몸에 남는칼로리
		int remainingCalories = DAILY_CALORIE_GOAL - netCalories;
		
		return remainingCalories;
	} 
	
	do {
    	//남은 칼로리가 0이하면 프로그램을 종료한다
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
            	inputExercise(&health_data); //운동입력 
                break;
                
            case 2:
            	inputDiet(&health_data); //식단입력 
            	
                break;
                
            case 3:
            	printHealthData(&health_data); // 건강데이터출력 
                break;
                
            case 4:
            	
    			printf("Exit the system.\n");
    			printf("=======================================================================\n");
                break;
                
            default:
                printf("[Error] Invalid option. \n");
                printf("Please try again! \n");
        }
    } while (choice!= 4 && calculateRemainingCalories(&health_data) > 0);

    return 0;
}

