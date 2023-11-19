DELIMITER $$

CREATE PROCEDURE MakeHotelReservation(
    IN customerID INT,
    IN checkInDate DATE,
    IN checkOutDate DATE,
    IN hotelID INT,
    IN roomType VARCHAR(50)
)
BEGIN
    DECLARE availableRoomID INT;
    DECLARE totalAmount DECIMAL(10, 2);
    DECLARE reservationID INT;

    -- Check room availability
    SELECT RoomID INTO availableRoomID
    FROM Rooms
    WHERE rooms.HotelID = hotelID
      AND rooms.RoomType = roomType
      AND (
        -- Check if the room is not reserved for the specified date range
        RoomID NOT IN (
          SELECT RoomID
          FROM roomreservations
          JOIN reservations r ON r.ReservationID = roomreservations.ReservationID
          WHERE (
            (r.CheckInDate >= checkInDate AND r.CheckInDate <= CheckOutDate) OR
            (r.CheckOutDate >= CheckInDate AND r.CheckOutDate <= CheckOutDate)
          )
        )
        -- OR Check if there are no rooms reserved for the specified type
        OR (
          SELECT COALESCE(COUNT(*), 0)
          FROM Rooms r
          WHERE r.HotelID = hotelID
            AND r.RoomType = roomType
        ) = 0
      )
    LIMIT 1;



    IF availableRoomID IS not NULL THEN
        -- Create reservation
        INSERT INTO Reservations (CustomerID, CheckInDate, CheckOutDate, TotalAmount, ReservationDate)
        VALUES (customerID, checkInDate, checkOutDate, 0, NOW());

        SET reservationID = LAST_INSERT_ID();

        -- Update room reservation
        SELECT RoomID as roomID INTO availableRoomID
        FROM Rooms
        WHERE rooms.HotelID = hotelID
        AND rooms.RoomType = roomType;

        INSERT INTO RoomReservations (ReservationID, RoomID)
        VALUES (reservationID, availableRoomID);

        -- Calculate total amount based on room price
        SELECT Price INTO totalAmount
        FROM Rooms
        WHERE RoomID = availableRoomID;

        -- Update total amount in the reservation
        UPDATE Reservations
        SET TotalAmount = totalAmount
        WHERE ReservationID = reservationID;

        -- Return reservation details
        SELECT reservationID AS ReservationID, checkInDate AS CheckInDate, checkOutDate AS CheckOutDate, totalAmount AS TotalAmount;
    ELSE
        -- No available rooms for the selected criteria
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'No available rooms for the selected criteria.';
    END IF;
END$$

DELIMITER ;
