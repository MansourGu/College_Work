// ANKIT SARRAF
// Reducer Class

package org.mansu.matrix;

import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

public class MatrixMultiplicationReducer extends
Reducer<Text, Text, Text, IntWritable> {

	public void reduce(Text key, Iterable<Text> values, Context context)
			throws IOException, InterruptedException {
		// 对于矩阵C的每一个元素对应标号位置进行求和
		int sum = 0;

		for (Text val : values) {
			sum += Integer.parseInt(val.toString());
			//求和后输出
		}

		System.out.println("Reducer Emiting : <" + key + "," + sum + ">");
		context.write(key, new IntWritable(sum));
	}
}