DELIMITER $$

CREATE TRIGGER UpdateRoomAvailability AFTER INSERT ON RoomReservations
FOR EACH ROW
BEGIN
    UPDATE Rooms
    SET IsBooked = 1
    WHERE RoomID = NEW.RoomID;
END $$

DELIMITER ;
