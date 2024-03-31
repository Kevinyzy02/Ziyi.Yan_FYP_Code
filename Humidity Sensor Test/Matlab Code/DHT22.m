
% Define serial port and parameters
comPort = 'COM4'; % Update this to match your Arduino's COM port
baudRate = 9600;

% Create a serial port object
arduinoSerial = serialport(comPort, baudRate);

% Prepare the live plot
figure;
hold on;
grid on;
xlabel('Time');
ylabel('Measurements');
title('Real-Time Temperature and Humidity Data');
tempPlot = animatedline('Color', 'r', 'DisplayName', 'Temperature (°C)');
humidPlot = animatedline('Color', 'b', 'DisplayName', 'Humidity (%)');
legend('show');

% Start reading and plotting data
startTime = datetime('now');
while true % Infinite loop to keep reading data
    % Read one line of data from the serial port
    dataStr = readline(arduinoSerial);
    
    % Parse the received data
    data = str2double(split(dataStr, ','));
    if length(data) == 2
        % Extract temperature and humidity
        temp = data(1);
        humid = data(2);
        
        % Calculate elapsed time
        elapsedTime = seconds(datetime('now') - startTime);
        
        % Add points to the plot
        addpoints(tempPlot, elapsedTime, temp);
        addpoints(humidPlot, elapsedTime, humid);
        drawnow; % Update the plot
        
        % Optionally, break the loop after some condition or include a stop mechanism
    else
        warning('Invalid data received: %s', dataStr);
    end
end

% Cleanup before exit (this part will not be reached if an infinite loop is used without a break condition)
clear arduinoSerial;
