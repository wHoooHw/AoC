import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;

public class puzzle1 {
    
    public static void main(String[] args){
        
        String filePath = "data.csv";
        int[] column1 = new int[1000];
        int[] column2 = new int[1000];         
        
        long startTime = System.nanoTime();

        try(BufferedReader br = new BufferedReader(new FileReader(filePath))){
            String line;
            int i = 0; 

            while((line = br.readLine()) != null){
                String[] columns = line.split("\\s+");
                column1[i] = Integer.parseInt(columns[0]);
                column2[i] = Integer.parseInt(columns[1]);
                i++;                

                // String column1 = columns[0];
                // String column2 = columns[1];

                // System.out.println("C1 " + column1 + " C2 " + column2);                
            }            
        }
        catch(IOException e){
            e.printStackTrace();            
        }        

        Arrays.sort(column1);
        Arrays.sort(column2);
        //System.out.println(check(column1, column2));        
        System.out.println(similarity(column1, column2));

        long endTime = System.nanoTime();
        long duration = (endTime - startTime) / 1000000; // Convert to milliseconds
        System.out.println("Runtime: " + duration + " ms");
    }

    public static int similarity(int[] x, int[] y){
        int similarityScore = 0, count = 0;         
        
        for (int i = 0; i < y.length; i++){
            for(int j = 0; j < x.length; j++){
                if(x[i] > y[j]){
                    continue;
                }

                if(x[i] < y[j]){
                    similarityScore += x[i] * count;
                    count = 0; 
                    break; 
                }
    
                if(x[i] == y[j]){
                    count++;
                }            
            }            
        }
                
        return similarityScore;
    }

    public static int check(int[] x, int[] y){
        int difference = 0;
        
        for(int i = 0; i < x.length; i++){
            difference += Math.abs(x[i] - y[i]);
        }

        return difference; 
    }
}
