//
//  cal_diets.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_DIETS 100      			// Maximum number of diets
#define MAX_FOOD_NAME_LEN 50		// Maximum length of the name of food


// list of diets 
static Diet diet_list[MAX_DIETS];
static int diet_list_size = 0;


/*
    description : read the information in "diets.txt"
*/

void loadDiets(const char* DIETFILEPATH) {
    FILE *file = fopen(DIETFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for diets! \n");
        return;
    }

     // ToCode: to read a list of the diets from the given file
    while (fscanf(file, "%[^,],%d\n", 
                  diet_list[diet_list_size].food_name, 
                  &diet_list[diet_list_size].calories_intake) == 2) {
                 diet_list_size++; //식단목록증가  
    	
        if (diet_list_size >= MAX_DIETS){
        	break; //최대식단 도달 반복종료  
		}
    }
    fclose(file);
}

/*
    description : to enter the selected diet and the total calories intake in the health data
    input parameters : health_data - data object to which the selected diet and its calories are added 
    return value : No
    
    operation : 1. provide the options for the diets to be selected
    			2. enter the selected diet and the total calories intake in the health data
*/

void inputDiet(HealthData* health_data) {
    int choice, i;
    
    // ToCode: to provide the options for the diets to be selected
    printf("The list of diets:\n");
    for (i = 0; i < diet_list_size; i++) {
        // 각 식단의 이름, 칼로리 출력
        printf("%d. %s (%d kcal)\n", i + 1, diet_list[i].food_name, 
               diet_list[i].calories_intake);
    }
    printf("%d. Exit\n", diet_list_size + 1); // 종료 옵션
	// ToCode: to enter the diet to be chosen with exit option
      do {
        printf("Choose a diet (1-%d) or %d to exit: ", diet_list_size, diet_list_size + 1);
        scanf("%d", &choice);
    } while (choice < 1 || choice > diet_list_size + 1);

    // 종료 선택 시 함수 종료
    if (choice == diet_list_size + 1) {
        printf("Exiting diet input.\n");
        return; // 종료선택시 함수종료  
    }

    // ToCode: to enter the selected diet in the health data
      if (health_data->diet_count < MAX_DIETS) {
        health_data->diet[health_data->diet_count] = diet_list[choice - 1]; // 선택한 식단 저장

    // ToCode: to enter the total calories intake in the health data
 	health_data->total_calories_intake += diet_list[choice - 1].calories_intake;
        
        // 식단 개수 증가 
        health_data->diet_count++;
        
        // 결과 출력
        printf("Added diet: %s, Calories intake: %d kcal\n", 
               diet_list[choice - 1].food_name, 
               diet_list[choice - 1].calories_intake);
    } else {
        printf("Maximum number of diets reached.\n");
    }
}



