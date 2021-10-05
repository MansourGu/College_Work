package org.mansu.matrix;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class MatrixMultiplication {
	public static void main(String[] args) throws IOException {
		Configuration conf = new Configuration();
		Job job = Job.getInstance(conf, "JobName");

		try {
			// 删除输出文件，如果输出文件已存在的情况下
			deleteFolder(conf, Constants.outputFilePath);
			deleteFolder(conf, Constants.finalResultPath);

			myMCRTask(job);
			
			new MatrixCProcessing().getMatrixC(
					Constants.outputFilePath + "/part-r-00000", Constants.finalResultPath);
			
			System.out.println("OPERATION SUCCESSFUL");
			System.out.println("FINAL OUTPUT WRITTEN TO FILE: " + Constants.finalResultPath);
		} catch(Exception e) {
			System.out.println("Cannot Continue ! Some Issue");
			System.out.println("Reason => " + e.getMessage());
		}
	}

	private static void myMCRTask(Job job)
			throws IllegalArgumentException,
			IOException,
			ClassNotFoundException,
			InterruptedException {
		job.setJarByClass(MatrixMultiplication.class);

		// 定义Mapper，Combiner，Reducer类
		job.setMapperClass(MatrixMultiplicationMapper.class);
		job.setCombinerClass(MatrixMultiplicationCombiner.class);
		job.setReducerClass(MatrixMultiplicationReducer.class);

		// 设定Mapper类的输入输出类型
		job.setMapOutputKeyClass(Text.class);
		job.setMapOutputValueClass(Text.class);

		// Combiner Output Key Value Types
		// Check this later

		// Reducer类 输出键值对类型
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(IntWritable.class);

		FileInputFormat.setInputPaths(job, new Path(Constants.inputFilePath));
		FileOutputFormat.setOutputPath(job, new Path(Constants.outputFilePath));

		if (!job.waitForCompletion(true))
			return;
		
		// 一旦Reducer类 任务结束 开始对输出文件进行处理
		// TODO: Create new File for Final Output Matrix
	}

	private static void deleteFolder(Configuration conf, String folderPath) throws IOException {
		// 删除文件夹
		FileSystem fs = FileSystem.get(conf);
		Path path = new Path(folderPath);
		if(fs.exists(path)) {
			fs.delete(path,true);
		}
	}
}
