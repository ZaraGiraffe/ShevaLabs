-- Insert a new reservation into the RoomReservations table
INSERT INTO RoomReservations (ReservationID, RoomID)
VALUES (1, 1);  -- Replace with valid ReservationID and RoomID values

-- Check the Rooms table to see if the IsBooked column has been updated
SELECT * FROM Rooms WHERE RoomID = 1;  -- Replace with the actual RoomID used in the INSERT

-- Verify that the IsBooked column is updated to 1 (meaning the room is booked)
