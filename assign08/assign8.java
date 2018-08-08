/*
	20151676 Hahn Seokju
	CSE241 OOP - assignment 8 Nap Schedule
*/

import java.io.*;
import java.util.*;

// defining a class for storing each schedule
// implement Comparable interface for comparing times between schedules 
class schedule implements Comparable <schedule>
{
	String start, end;
	// override compareTo method
	public int compareTo(schedule another) { return start.compareTo(another.start); }
	// method for converting time only in minutes
	public static int convertHtoM(String time)
	{
		String[] converted = time.split(":");
		return Integer.parseInt(converted[0]) * 60 + Integer.parseInt(converted[1]);
	}
	// get a time difference between two schedules
	public int difference(schedule previous)
	{
		int currentStart = convertHtoM(start);
		int previousEnd = convertHtoM(previous.end);
		return currentStart - previousEnd;
	}
}

// main class
public class assign8
{
	// for file input and printing the result
	Scanner in; PrintStream out;
	// store each schedule in each test case to the list
	schedule[] scheduleList;
	// refering the start time of the possible longest nap
	String startTimeString;
	// store information of how long the professor can have a nap, in each day
	int howLong, day = 1;

	// get input and call other methods
	public assign8(InputStream i, PrintStream o)
	{
		// get file input from file to inputStream, yield output from System.out to printStream
		in = new Scanner(i); out = o;
		while (in.hasNext()) { initialize(); judge(); print(); day++; }
		in.close();
	}
	
	public void initialize()
	{
		howLong = 0;

		int numOfSchedule = in.nextInt();
		if (numOfSchedule < 1 || numOfSchedule > 100) System.exit(-1);
		scheduleList = new schedule[numOfSchedule + 2];
		// constraint 1 : all times be greater than equal to 10:00
		scheduleList[numOfSchedule] = new schedule();
		scheduleList[numOfSchedule].start = "00:00";
		scheduleList[numOfSchedule].end = "10:00";
		// constraint 2 : all times be smaller than equal to 18:00
		scheduleList[numOfSchedule + 1] = new schedule();
		scheduleList[numOfSchedule + 1].start = "18:00";
		scheduleList[numOfSchedule + 1].end = "00:00";
		// append all the schedule in a day
		for (int i = 0; i < numOfSchedule; i++)
		{
			scheduleList[i] = new schedule();
			scheduleList[i].start = in.next();
			scheduleList[i].end = in.next();

			in.nextLine();
		}
		Arrays.sort(scheduleList); // sort all the schedule
	}

	public void judge()
	{
		schedule previousTime = scheduleList[0];
		schedule currentTime = scheduleList[1];
		int difference;
		// calculate duration of nap between neighboring schedules
		for (int i = 1; i < scheduleList.length; i++)
		{
			currentTime = scheduleList[i];
			difference = currentTime.difference(previousTime);
			// update longest nap duration 
			if (difference > howLong)
			{
				howLong = difference;
				startTimeString = previousTime.end;
			} previousTime = currentTime;
		}
	}

	private void print()
	{
		// print the result
		if (howLong < 60)
		{ 
			String message = "Day #%d: the longest nap starts at %s and will last for %d minutes.";
			out.println(String.format(message, day, startTimeString, howLong)); 
		}
		else 
		{ 
			String message = "Day #%d: the longest nap starts at %s and will last for %d hours and %d minutes.";
			out.println(String.format(message, day, startTimeString, howLong / 60, howLong % 60)); 
		}
	}

	public static void main(String[] args) throws IOException
	{
		// call file from 'input.txt' and transform contents into InputStream
		File file = new File("input.txt");
		InputStream input = new FileInputStream(file);
		new assign8(input, System.out);
	}
}
