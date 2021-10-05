// 这个用来存放一些参数

package org.mansu.matrix;

public interface Constants {
	final String inputFilePath = "/input"; //输入文件路径
	final String outputFilePath = "/matrixMultiplication/output";//输出文件路径
	final String finalResultPath = "/matrixMultiplication/finalResult/MatrixC.txt";//输出文件名
	final int DIMENSIONS = 100;//矩阵的维数
	final double Threshhold = 0.3;//判断是否替换当前值的阈值
}