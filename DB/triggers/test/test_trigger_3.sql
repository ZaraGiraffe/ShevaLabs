-- Insert a new promotion into the Promotions table without specifying PromotionID
INSERT INTO Promotions (HotelID, PromotionName, Description, DiscountPercentage, StartDate, EndDate, IsCouponCodeRequired)
VALUES (1, 'Summer Discount', 'Get 20% off', 20.00, '2023-11-08', '2023-11-30', 1);



-- Check the generated coupon code for the newly inserted promotion
SELECT CouponCode FROM Promotions WHERE PromotionID = LAST_INSERT_ID();

-- Verify that the CouponCode column has been updated with a unique coupon code
