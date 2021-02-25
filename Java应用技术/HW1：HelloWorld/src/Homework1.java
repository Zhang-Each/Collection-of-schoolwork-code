import java.util.Scanner;

public class Homework1 {
    public static void main(String args[]) {

        System.out.println("Input 1 to change decimal to hexadecimal and 2 to change hexadecimal to demical.");
        Scanner input = new Scanner(System.in);
        int kind = input.nextInt();
        if(kind == 1) {
            System.out.println("Please input a decimal number:");
            int number = input.nextInt();
            changtoHexadecimal(number);
        }
        else if(kind == 2) {
            System.out.println("Please input a hexadecimal number:");
            String number = input.next();
            changeToDecimal(number);
        } else {
            System.out.println("Input Error, please try again!");
        }
    }

    public static void changeToDecimal(String value) {
        if(value.charAt(0) == '0' && (value.charAt(1) == 'x' || value.charAt(1) == 'X')) {
            value = value.substring(2);
        }
        int i, result = 0;
        for(i=0; i<value.length(); i++) {
            int temp = 0;
            if(value.charAt(i) >= '0' && value.charAt(i) <= '9')
                temp = value.charAt(i) - '0';
            else if(value.charAt(i) >= 'a' && value.charAt(i) <= 'f')
                temp = value.charAt(i) - 'a' + 10;
            else if(value.charAt(i) >= 'A' && value.charAt(i) <= 'F')
                temp = value.charAt(i) - 'A' + 10;
            else {
                System.out.println("Error input! please try again!");
                return;
            }
            result = result*16 + temp;
        }
        System.out.println(result);
    }

    public static void changtoHexadecimal(int value) {
        StringBuilder result = new StringBuilder();
        while(value != 0) {
            int temp = value%16;
            if(temp <= 9 && temp >= 0) {
                result.append(Integer.toString(temp));
            }
            else {
                result.append('a'+temp-10);
            }
            value /= 16;
        }
        result.append("x0");
        result = result.reverse();
        System.out.println(result);
    }
}

