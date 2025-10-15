#include <stdio.h>

int main(void){
    float temp;
    printf("Enter the temperature value: ");
    scanf(" %f", &temp);

    char scale;
    printf("Choose temperature scale of the input value ([F]ahrenheit, [C]elsius, or [K]elvin): ");
    scanf(" %c", &scale);

    char convert;
    printf("Choose the conversion target ([F]ahrenheit, [C]elsius, or [K]elvin]): ");
    scanf(" %c", &convert);

    float result;
    if (scale=='C' || scale=='c'){
        if (convert=='C' || convert=='c'){
            result = temp;
        }
        else if(convert=='F' || convert=='f'){
            result=(temp*9.0/5.0)+32;
        }
        else if (convert=='K' || convert=='k'){
            result = temp+273.15;
        }
        else{
            printf("Invalid conversion target!\n");
            return 1;
        }
    }
    else if (scale == 'F' || scale == 'f'){
        if (convert=='C' || convert=='c'){
            result = (temp-32)*5.0/9.0;
        }
        else if(convert=='F' || convert=='f'){
            result=temp;
        }
        else if (convert=='K' || convert=='k'){
            result = (temp-32)*5.0/9.0+273.15;
        }
        else{
            printf("Invalid conversion target!\n");
            return 1;
        }
    }
    else if (scale=='K' || scale=='k'){
        if (convert=='C' || convert=='c'){
            result = temp-273.15;
        }
        else if(convert=='F' || convert=='f'){
            result=(temp-273.15)*9.0/5.0+32;
        }
        else if (convert=='K' || convert == 'k'){
            result = temp;
        }
        else{
            printf("Invalid conversion target!\n");
            return 1;
        }
    }
    else{
        printf("Invalid input scale!\n");
        return 1;
    }
    printf("Converted temperature: %.2f %c\n", result, convert);
    float final;
    if (convert=='c' || convert=='C'){
        final==result;
    }
    else if (scale=='C' || scale=='c'){
        final == temp;
    }
    else if (convert=='F' || convert=='f'){
        final = (result-32)*5.0/9.0;
    }
    else if (convert=='K' || convert=='k'){
        final = result-273.15;
    }
    
    if (final<0){
        printf("Temperature category: Freezing\n");
        printf("Weather advisory: Wear layers");
    }
    else if (final<10){
        printf("Temperature category: Cold\n");
        printf("Weather advisory: Bring a jacket");
    }
    else if (final<25){
        printf("Temperature category: Comfortable\n");
        printf("Weather advisory: Enjoy the weather!");
    }
    else if (final<35){
        printf("Temperature category: Hot\n");
        printf("Weather advisory: Drink lots of water");
    }
    else{
        printf("Temperature category: Extreme Heat\n");
        printf("Weather advisory: Stay inside!");
    }
    return 0;
}