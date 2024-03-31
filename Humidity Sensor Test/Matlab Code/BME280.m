% Make sure to close any existing serial port connections
delete(instrfindall);

% Set up the serial port connection (COM3 is an example, replace with your actual port)
s = serial('COM4', 'BaudRate', 115200);
fopen(s);

% Prepare the figure
figure;
hold on;
grid on;

% Initialize buffers for temperature, humidity, and timestamps
tempData = [];
humiData = [];
tempTimeStamps = [];
humiTimeStamps = [];
startTime = tic; % Start a timer

% Use flags to indicate new data
newTempData = false;
newHumiData = false;

while true
    % Read a line of data from the serial port
    data = fgetl(s);

    % Parse temperature and humidity data from the line
    if contains(data, 'Temperature')
        temp = sscanf(data, 'Temperature: %f');
        tempData = [tempData, temp]; % Append new temperature data
        tempTimeStamps = [tempTimeStamps, toc(startTime)]; % Append timestamp for temperature
        newTempData = true;
    elseif contains(data, 'Humidity')
        humi = sscanf(data, 'Humidity: %f');
        humiData = [humiData, humi]; % Append new humidity data
        humiTimeStamps = [humiTimeStamps, toc(startTime)]; % Append timestamp for humidity
        newHumiData = true;
    end

    % Update plots if both new temperature and humidity data have been received
    if newTempData && newHumiData
        % Plot temperature
        subplot(2,1,1);
        plot(tempTimeStamps, tempData, 'r-');
        xlabel('Time (seconds)');
        ylabel('Temperature (°C)');
        title('Real-time Temperature Data');
        
        % Plot humidity
        subplot(2,1,2);
        plot(humiTimeStamps, humiData, 'b-');
        ylabel('Humidity (%)');
        xlabel('Time (seconds)');
        title('Real-time Humidity Data');

        drawnow; % Update the plots

        % Reset flags
        newTempData = false;
        newHumiData = false;
    end
end

% Clean up
fclose(s);
delete(s);
clear s;

