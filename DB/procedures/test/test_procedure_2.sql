-- Execute the stored procedure
CALL MakeHotelReservation(1, '2024-11-15', '2024-11-20', 1, 'Single');

-- Check the Reservations table for the newly created reservation
SELECT * FROM Reservations WHERE CustomerID = 1; -- Assuming 1 is the customer ID used in the procedure

-- Check the RoomReservations table to see which room is associated with the reservation
SELECT * FROM RoomReservations WHERE ReservationID = LAST_INSERT_ID();

-- Check the Rooms table for the room details (e.g., price, room type) associated with the reservation
SELECT * FROM Rooms WHERE RoomID = (SELECT RoomID FROM RoomReservations WHERE ReservationID = LAST_INSERT_ID());

-- Check the Customers table for customer information
SELECT * FROM Customers WHERE CustomerID = 1; -- Assuming 1 is the customer ID used in the procedure
