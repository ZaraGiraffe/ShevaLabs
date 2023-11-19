-- This function calculates the average rating of a hotel based on its reviews.
CREATE FUNCTION CalculateAverageHotelRating(hotelID INT) RETURNS DECIMAL(3, 2) DETERMINISTIC
BEGIN
    DECLARE avgRating DECIMAL(3, 2);
    SELECT AVG(Rating) INTO avgRating
    FROM Reviews
    WHERE Reviews.HotelID = hotelID;
    RETURN avgRating;
END;
