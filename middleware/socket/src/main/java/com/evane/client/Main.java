package com.evane.client;

import java.io.*;
import java.net.Socket;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    public static boolean ValidateIP(String input_IP)
    {
        String numRange = "(\\d{1,2}|(0|1)\\" + "d{2}|2[0-4]\\d|25[0-5])" + "\\."
                + "(\\d{1,2}|(0|1)\\" + "d{2}|2[0-4]\\d|25[0-5])" + "\\."
                + "(\\d{1,2}|(0|1)\\" + "d{2}|2[0-4]\\d|25[0-5])" + "\\."
                + "(\\d{1,2}|(0|1)\\" + "d{2}|2[0-4]\\d|25[0-5])";

        Pattern ip_pattern = Pattern.compile(numRange);
        Matcher match= ip_pattern.matcher(input_IP);
        return match.matches();
    }

    public static void main(String[] args) {
        String address = "";
        Scanner scanner = new Scanner(System.in);
        System.out.println("Entrez votre adresse IP : ");
        address = scanner.nextLine();

        if (!ValidateIP((address))) address = "localhost";

        try (Socket socket = new Socket(address, 5000)) {
            // Socket incoming stream
            DataInputStream inputStream = new DataInputStream(socket.getInputStream());
            // Socket outgoing stream
            DataOutputStream outputStream = new DataOutputStream(socket.getOutputStream());
            // reading the input from server
            BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));

            // returning the output to the server : true statement is to flush the buffer
            // otherwise
            // we have to do it manually
            PrintWriter output = new PrintWriter(socket.getOutputStream(), true);

            // storing the user input
            String userInput;

            // Loop closes when user enters exit command
            do {
                // Print server response
                System.out.println(inputStream.readUTF());
                // Get keyboard input
                System.out.print("> ");
                userInput = scanner.nextLine();
                // Send request to the server
                outputStream.writeUTF(userInput);
                // Wait a bit for server to respond
                Thread.sleep(500);
            } while (!userInput.equals("exit"));

            System.out.println("Closing connection...");
            socket.close();
            inputStream.close();
            outputStream.close();

        } catch (Exception e) {
            System.out.println("Exception occurred in client main: " + e.getStackTrace());
        }
    }
}