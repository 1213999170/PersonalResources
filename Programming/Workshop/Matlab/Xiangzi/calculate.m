function [alpha] = calculate(v)
    % :::::::::::::::::::::::::::::::::::
    % Parameters
    pK = 9;
    pL = 5;
    u_rows = 21;
    u_cols = 25; % u_cols = p_rows
    p_rows = 25;
    p_cols = 25;

    % :::::::::::::::::::::::::::::::::::
    % Initialize
    Pdata = xlsread('P.xlsx','Sheet1');
    P = reshape(Pdata, pK, pL, p_rows, p_cols);
    
    U0 = zeros(u_rows, u_cols);
    U0(1, 1) = 1;

    % player_num = 0;
    n = 0;
    disp('hello');
    % :::::::::::::::::::::::::::::::::::
    % Play Game
    for round = 1 : pK
        p_judge = 0;
        while p_judge <= 0.999
            U1 = zeros(u_rows, u_cols);
            U1(1,:) = U0(1,:)*getP(P,n+1,1);
            U1(2,:) = U0(1,:)*getP(P,n+1,2)+U0(2,:)*getP(P,n+1,1);
            U1(3,:) = U0(1,:)*getP(P,n+1,3)+U0(2,:)*getP(P,n+1,2)+U0(3,:)*getP(P,n+1,1);
            U1(4,:) = U0(1,:)*getP(P,n+1,4)+U0(2,:)*getP(P,n+1,3)+U0(3,:)*getP(P,n+1,2)+U0(4,:)*getP(P,n+1,1);
            for x = 5 : 21
                U1(x,:) = U0(x-4,:)*getP(P,n+1,5) ...
                        + U0(x-3,:)*getP(P,n+1,4) ...
                        + U0(x-2,:)*getP(P,n+1,3) ...
                        + U0(x-1,:)*getP(P,n+1,2) ...
                        + U0(x  ,:)*getP(P,n+1,1);
            end
            p_judge = ones(1,u_rows) * U1(:,u_cols);
            % player_num = n + 1;
            n = mod(n + 1, pK);% mod(player_num, pK);

            U0 = U1;
        end

        U0(:, 2:u_cols) = 0;
    end

    alpha = (0:u_rows - 1) * U0(:, 1);
end

function [ret] = getP(P, k, l)
    s = size(P(k, l, :, :));
    ret = reshape(P(k, l, :, :), s(3:4));
end
