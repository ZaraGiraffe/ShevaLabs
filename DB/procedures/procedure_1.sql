DELIMITER $$

CREATE PROCEDURE GetAvailableRooms(HotelID INT, CheckInDate DATE, CheckOutDate DATE)
BEGIN
    -- Drop the temporary table if it exists
    DROP TEMPORARY TABLE IF EXISTS AvailableRooms;

    -- Create a temporary table to store the available rooms
    CREATE TEMPORARY TABLE AvailableRooms AS
    SELECT r.RoomID, r.RoomNumber, r.RoomType, r.BedType, r.MaxOccupancy, r.Price, r.Description
    FROM Rooms AS r
    WHERE r.HotelID = HotelID
    AND r.RoomID NOT IN (
        SELECT rr.RoomID
        FROM RoomReservations AS rr
        JOIN Reservations AS r2 ON r2.ReservationID = rr.ReservationID
        WHERE r2.CheckInDate <= CheckOutDate
        AND r2.CheckOutDate >= CheckInDate
    );
END $$

DELIMITER ;
