% Define the range of theta
theta = linspace(0, 2*pi, 1000); % from 0 to 2*pi with 1000 points

% Calculate r based on the given equation
r = 5 * cos(4 * theta);

% Convert polar coordinates to Cartesian coordinates
x = r .* cos(theta);
y = r .* sin(theta);

% Time (theta) values
time = theta;  % Time can be considered as the angle here

% Write the data to a CSV file
data = [x' y' time'];
csvwrite('polar_data.csv', data);

% Inform the user
disp('Data has been written to "polar_data.csv".');