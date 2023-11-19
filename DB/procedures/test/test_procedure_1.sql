-- Call the stored procedure to populate the AvailableRooms table
CALL GetAvailableRooms(1, '2023-11-08', '2023-11-10');

-- Select available rooms from the temporary table
SELECT * FROM AvailableRooms;
