// Developer: ANKIT SARRAF
// Combiner Class

package org.mansu.matrix;

import java.io.IOException;

import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

// Combiner 的输出格式必须与 Mapper 的输出格式一致
public class MatrixMultiplicationCombiner extends
Reducer<Text, Text, Text, Text> {
	private int tempStorage [][] = new int[Constants.DIMENSIONS][Constants.DIMENSIONS];
	private int currentIndex [] = new int[Constants.DIMENSIONS];

	public void reduce(Text key, Iterable<Text> values, Context context)
			throws IOException, InterruptedException {
		for(int p = 0 ; p < Constants.DIMENSIONS ; p++) {
			currentIndex[p] = 0;
		}

		for (Text val : values) {
			String actualKey = val.toString().substring(1, val.toString().length() - 1);

			// 获取 j 标号 和 实际值
			int j = Integer.parseInt(actualKey.split(",")[0]);
			int valJ = Integer.parseInt(actualKey.split(",")[1]);

			tempStorage[j][currentIndex[j]] = valJ;
			currentIndex[j]++;
		}

		for(int i = 0 ; i < Constants.DIMENSIONS ; i++) {
			tempStorage[i][0] = tempStorage[i][0] * tempStorage[i][1];
			//将A、B两矩阵对应位置的值相乘
			System.out.println("Combiner Emiting : <" + key + "," + tempStorage[i][0] + ">");
			context.write(key, new Text("" + tempStorage[i][0]));
		}
	}
}
