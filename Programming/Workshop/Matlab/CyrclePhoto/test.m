function test(input, output, gap)
    % input = 'C:\Users\Administrator\Desktop\mmexport1496502927066.jpg'
    % output = 'C:\Users\Administrator\Desktop\mmexport1496502927066_cycle.jpg'

    imdata = imread(input);

    cycledata = uint8(ones(size(imdata)) * 255);

    [m, n, l] = size(cycledata);
    center = [round(m / 2), round(n / 2)];
    for r = 1 : gap : n / 2 - 1 
        x = round(r); y = 0;
        while (true)
            ix = center(1) + x;
            iy = center(2) + y;
            cycledata(ix, iy, :) = imdata(ix, iy, :);
            
            if x > 0
                dy = 1;
            elseif x < 0
                dy = -1;
            elseif y > 0
                dy = -1;
            else
                dy = 1;
            end
            
            if y > 0
                dx = -1;
            elseif y < 0
                dx = 1;
            elseif x > 0
                dx = -1;
            else
                dx = 1;
            end
            
            dist1 = abs((x + dx)^2 +  y^2       - r^2);
            dist2 = abs((x + dx)^2 + (y + dy)^2 - r^2);
            dist3 = abs( x^2       + (y + dy)^2 - r^2);
            
            if dist1 <= dist2 && dist1 <= dist3
                x = x + dx;
            elseif dist2 <= dist1 && dist2 <= dist3
                x = x + dx;
                y = y + dy;
            else
                y = y + dy;
            end
            
            if x == r && y == 0
                break;
            end
        end
    end

    imshow(cycledata);
    imwrite(cycledata, output);
end
