DELIMITER $$

CREATE TRIGGER UpdateHotelRating AFTER INSERT ON Reviews
FOR EACH ROW
BEGIN
    DECLARE avgRating DECIMAL(3, 2);
    SELECT AVG(Rating) INTO avgRating FROM Reviews WHERE HotelID = NEW.HotelID;
    UPDATE Hotels SET StarRating = avgRating WHERE HotelID = NEW.HotelID;
END $$

DELIMITER ;
