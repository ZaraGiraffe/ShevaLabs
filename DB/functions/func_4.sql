DELIMITER $$
CREATE FUNCTION CalculateTotalRevenueForHotel(HotelID INT) RETURNS DECIMAL(10, 2) DETERMINISTIC
BEGIN
    DECLARE TotalRevenue DECIMAL(10, 2);

    SELECT SUM(Payments.Amount) INTO TotalRevenue
    FROM Reservations
    INNER JOIN Payments ON Reservations.ReservationID = Payments.ReservationID
    INNER JOIN Rooms ON Reservations.ReservationID = Rooms.HotelID
    WHERE Rooms.HotelID = HotelID;

    RETURN TotalRevenue;
END;
$$
DELIMITER ;
