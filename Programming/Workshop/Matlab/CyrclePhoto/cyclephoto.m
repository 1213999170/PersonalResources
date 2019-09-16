function cyclephoto(input, output, gap, delta)
    % input = 'C:\Users\Administrator\Desktop\mmexport1496502927066.jpg'
    % output = 'C:\Users\Administrator\Desktop\mmexport1496502927066_cycle.jpg'

    imdata = imread(input);
    if ndims(imdata) == 3
        greydata = rgb2gray(imdata);
    end

    cycledata = uint8(ones(size(greydata)) * 255);

    [m, n] = size(cycledata);
    center = [m / 2, n / 2];
    for r = 1 : gap : n / 2
        for theta = 0 : delta / r : 2 * pi
            point = int32(center + r * [cos(theta), sin(theta)]);
            x = point(1);
            y = point(2);
            if x > 0 && x <= m && y > 0 && y <= n
                cycledata(x, y) = greydata(x, y);
            end
        end
    end

    imshow(cycledata);
    imwrite(cycledata, output);
end
