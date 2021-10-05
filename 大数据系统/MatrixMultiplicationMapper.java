// Mapper 类

package org.mansu.matrix;

import java.awt.*;
import java.io.IOException;
import java.util.ArrayList;

import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

public class MatrixMultiplicationMapper extends
Mapper<Object, Text, Text, Text> {
	private ArrayList<ArrayList<Integer>> matrixA = new ArrayList<ArrayList<Integer>>();//用二维列表存储矩阵A
	private ArrayList<ArrayList<Integer>> matrixB = new ArrayList<ArrayList<Integer>>();//用二维列表存储矩阵A

	private int matAi = 0;//记录矩阵A的行号
	private int matBj = 0;//记录矩阵B的列号

	private String currentMatrix = "";

	public void map(Object key, Text value, Context context)
			throws IOException, InterruptedException {
		//读取每一个行
		String [] matrixValues = value.toString().split("\\s+");

		ArrayList<Integer> eachRow = new ArrayList<Integer>();
		if(!matrixValues[0].equals("MatrixA") && !matrixValues[0].equals("MatrixB")) {
			for(String matrixValue: matrixValues) {
				eachRow.add(Integer.parseInt(matrixValue));
			}
			if(currentMatrix.equals("MatrixA")) {
				matrixA.add(eachRow);
				matAi++;

				if(matAi == Constants.DIMENSIONS)
				{

					//对整个矩阵进行预处理
					for (int i = 0; i<Constants.DIMENSIONS; i++)
						for (int j = 0 ; j < Constants.DIMENSIONS ; j++)
						{
							int x = matrixA.get(i).get(j);
							int count_all = 0;
							int count_times = 0;
							if (i - 1 >= 0)//左
							{
								count_all+=matrixA.get(i-1).get(j);
								count_times++;
							}
							if (j-1>=0)//上
							{
								count_all+=matrixA.get(i).get(j-1);
								count_times++;
							}
							if (i+1<= Constants.DIMENSIONS-1)//右
							{
								count_all+=matrixA.get(i+1).get(j);
								count_times++;
							}
							if (j+1<=Constants.DIMENSIONS-1)//下
							{
								count_all+=matrixA.get(i).get(j+1);
								count_times++;
							}
							if (i-1>=0 && j-1>=0)//左上
							{
								count_all+=matrixA.get(i-1).get(j-1);
								count_times++;
							}
							if (i-1>=0 && j+1<=Constants.DIMENSIONS-1)//左下
							{
								count_all+=matrixA.get(i-1).get(j+1);
								count_times++;
							}
							if (i+1 <=Constants.DIMENSIONS-1 && j+1<=Constants.DIMENSIONS-1)//右下
							{
								count_all+=matrixA.get(i+1).get(j+1);
								count_times++;
							}
							if (i+1 <=Constants.DIMENSIONS-1 && j-1>=0)//右上
							{
								count_all+=matrixA.get(i+1).get(j-1);
								count_times++;
							}

							float x_prime = (float)count_all / count_times;//求当前值一圈值的均值
							float ratio = (x_prime - x)/ (float)x;//均值计算出来之后并计算均值与当前值相对误差
							if (Math.abs(ratio) >= Constants.Threshhold)//当相对误差大于一个阈值时，我们用均值替换当前值
							{
								matrixA.get(i).set(j,(int)x_prime);
							}
						}


					// 输出 Mtrix A 的键值对
					for(int i = 0 ; i < Constants.DIMENSIONS ; i++) {
						for(int j = 0 ; j < Constants.DIMENSIONS ; j++) {
							for(int k = 0 ; k < Constants.DIMENSIONS ; k++) {
								String matAKey =
										new String("(" + i + "," + k + ")");//输出key
								String matAValue =
										new String("(" + j + "," + matrixA.get(i).get(j) + ")");//输出value

								System.out.println("Emiting A : <" + matAKey + "," + matAValue + ">");
								context.write(new Text(matAKey), new Text(matAValue));
							}
						}
					}
				}
			}
			else if(currentMatrix.equals("MatrixB")) {
				matrixB.add(eachRow);
				matBj++;

				if(matBj == Constants.DIMENSIONS) {


					for (int i = 0; i<Constants.DIMENSIONS; i++)
						for (int j = 0 ; j < Constants.DIMENSIONS ; j++)
						{
							int x = matrixB.get(i).get(j);
							int count_all = 0;
							int count_times = 0;
							if (i - 1 >= 0)//左
							{
								count_all+=matrixB.get(i-1).get(j);
								count_times++;
							}
							if (j-1>=0)//上
							{
								count_all+=matrixB.get(i).get(j-1);
								count_times++;
							}
							if (i+1<= Constants.DIMENSIONS-1)//右
							{
								count_all+=matrixB.get(i+1).get(j);
								count_times++;
							}
							if (j+1<=Constants.DIMENSIONS-1)//下
							{
								count_all+=matrixB.get(i).get(j+1);
								count_times++;
							}
							if (i-1>=0 && j-1>=0)//左上
							{
								count_all+=matrixB.get(i-1).get(j-1);
								count_times++;
							}
							if (i-1>=0 && j+1<=Constants.DIMENSIONS-1)//左下
							{
								count_all+=matrixB.get(i-1).get(j+1);
								count_times++;
							}
							if (i+1 <=Constants.DIMENSIONS-1 && j+1<=Constants.DIMENSIONS-1)//右下
							{
								count_all+=matrixB.get(i+1).get(j+1);
								count_times++;
							}
							if (i+1 <=Constants.DIMENSIONS-1 && j-1>=0)//右上
							{
								count_all+=matrixB.get(i+1).get(j-1);
								count_times++;
							}
							float x_prime = (float)count_all / count_times;
							float ratio = (x_prime - x)/ (float)x;
							if (Math.abs(ratio) >= Constants.Threshhold)
							{
								matrixB.get(i).set(j,(int)x_prime);
							}
						}

					// 输出 Matrix B 的 键值对
					for(int j = 0 ; j < Constants.DIMENSIONS ; j++) {
						for(int k = 0 ; k < Constants.DIMENSIONS ; k++) {
							for(int i = 0 ; i < Constants.DIMENSIONS ; i++) {
								String matBKey =
										new String("(" + i + "," + k + ")");//输出key
								String matBValue =
										new String("(" + j + "," + matrixB.get(j).get(k) + ")");//输出value

								System.out.println("Emiting B : <" + matBKey + "," + matBValue + ">");
								context.write(new Text(matBKey), new Text(matBValue));
							}
						}
					}
				}
			}
		}
		else {
			if(matrixValues[0].equals("MatrixA")) {
				currentMatrix = new String("MatrixA");
			} else {
				currentMatrix = new String("MatrixB");
			}
		}
	}
}