% Specify the serial port Arduino is connected to
comPort = 'COM4'; % Update this to your Arduino's COM port
baudRate = 9600;

% Create serial object
if ~isempty(instrfind)
    fclose(instrfind);
    delete(instrfind);
end
arduinoSerial = serial(comPort, 'BaudRate', baudRate);

% Open serial connection
fopen(arduinoSerial);

% Prepare the figure for plotting
figure;
hold on;

% Initialize buffers for temperature, humidity, and timestamps
tempData = [];
humiData = [];
timestamps = [];
startTime = tic; % Start a timer

% Read and plot data in real-time
while true
    if arduinoSerial.BytesAvailable > 0
        dataLine = fgetl(arduinoSerial); % Read line from serial
        [tempStr, humidityStr] = strtok(dataLine, ',');
        temp = str2double(strrep(tempStr, 'T:', ''));
        humidity = str2double(strrep(humidityStr, ',H:', ''));
        
        % Append data and timestamp
        tempData = [tempData, temp];
        humiData = [humiData, humidity];
        timestamps = [timestamps, toc(startTime)];
        
        % Plot temperature
        subplot(2,1,1);
        plot(timestamps, tempData, 'r-');
        xlabel('Time (seconds)');
        ylabel('Temperature (°C)');
        title('Real-time Temperature Data');
        grid on;
        
        % Plot humidity
        subplot(2,1,2);
        plot(timestamps, humiData, 'b-');
        xlabel('Time (seconds)');
        ylabel('Humidity (%)');
        title('Real-time Humidity Data');
        grid on;
        
        drawnow; % Update the plots
    end
end

% Remember to close the serial port when you're done
fclose(arduinoSerial);
delete(arduinoSerial);
clear arduinoSerial;

