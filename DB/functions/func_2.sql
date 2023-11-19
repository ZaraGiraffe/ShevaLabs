-- This function calculates the total price for a reservation based on the selected room(s) and their prices.
DELIMITER $$

CREATE FUNCTION CalculateTotalPrice(ReservationID INT) RETURNS DECIMAL(10, 2) READS SQL DATA
BEGIN
    DECLARE Total DECIMAL(10, 2);
    SELECT SUM(Price) INTO Total
    FROM Rooms
    INNER JOIN RoomReservations ON Rooms.RoomID = RoomReservations.RoomID
    WHERE RoomReservations.ReservationID = ReservationID;
    RETURN Total;
END $$

DELIMITER ;
