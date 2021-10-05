// 用来得到最终结果（通过最后Reduce的结果）的MtrixC = A X B得Java程序
// To obtain the final Matrix C = A X B

package org.mansu.matrix;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FSDataOutputStream;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;

public class MatrixCProcessing {
	private int [][] MatrixC;

	MatrixCProcessing() {
		MatrixC = new int[Constants.DIMENSIONS][Constants.DIMENSIONS];
	}

	void usage () {
		System.out.println("Usage : HadoopDFSFileReadWrite <inputfile> <output file>");
		System.exit(1);
	}

	void printErrorMessage(String str) {
		System.out.println(str);
		return;
	}

	public void getMatrixC(String inputFileName, String outputFileName) throws IOException {
		Configuration conf = new Configuration();
		FileSystem fs = FileSystem.get(conf);

		// Hadoop DFS deals with Path
		Path inFile = new Path(inputFileName);
		Path outFile = new Path(outputFileName);

		// Check if input/output are valid
		if (!fs.exists(inFile)) {
			printErrorMessage("Input file not found");
			throw new IOException();
		} if (!fs.isFile(inFile)) {
			printErrorMessage("Input should be a file");
			throw new IOException();
		} if (fs.exists(outFile)) {
			printErrorMessage("Final Page Rank Input File Exists. Deleting it");
			fs.delete(outFile, true);
		}

		BufferedReader in = new BufferedReader(new InputStreamReader(fs.open(inFile)));
		FSDataOutputStream out = fs.create(outFile);

		try{
			String index;
			int valueAtIndex;
			String line;

			while((line = in.readLine()) != null) {
				// Line has the pre-processed output
				index = (line.split("\\s+"))[0];
				valueAtIndex = Integer.parseInt((line.split("\\s+"))[1]);

				index = index.substring(1, index.length() - 1);
				int i = Integer.parseInt((index.split(","))[0]);
				int j = Integer.parseInt((index.split(","))[1]);

				MatrixC[i][j] = valueAtIndex;
			}

			out.writeBytes("Matrix C\n");
			for(int i = 0 ; i < Constants.DIMENSIONS ; i++) {
				for(int j = 0 ; j < Constants.DIMENSIONS ; j++) {
					out.writeBytes(MatrixC[i][j] + "\t");
				}
				out.writeBytes("\n");
			}
		} catch(Exception e) {
			System.out.println("Un-understandable Exception : " + e.getMessage());
		} finally {
			in.close();
			out.close();
		}
	}
}