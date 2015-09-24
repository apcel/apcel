function MyVector()
    beep off
    k = 0;
    while (k ~= 8)
        k = input('1) Вывод вектора на экран\n2) Заполнение вектора с помощью датчика случайных чисел \n3) Сортировка методом \"Пузырька\" \n4) Сортировка методом вставок \n5) Сортировка подсчётом \n6) Бинарный поиск элемента вектора \n7) Интерполяционный поиск элемента вектора \nВведите \"8\"" для выхода\n//Enter \"8\"" to exit\n<<<< ');
        tic
        switch k
        case 1%Вывод вектора на экран
            vect
        case 2%Заполнение вектора с помощью датчика случайных чисел
            n = input('Введите размер вектора: ');
             vect = round(rand(1, n) * 1000);
        case 3%Сортировка методом "Пузырька"
            vect = sortBubble(vect);
        case 4% Сортировка методом вставок
            vect = sortInsertion(vect);
        case 5%Сортировка подсчётом
           vect = sortCount(vect);
        case 6%Бинарный поиск элемента вектора
            key = input('Enter search key: ');
            tic
            index = findBinary(vect, key);
        case 7%Интерполяционный поиск элемента вектора
            key = input('Enter search key: ');
            tic
            index = findInterpolation(vect, key);
        case 8
            break;
        otherwise
            disp('Sorry, your input "'); k
             disp('" was not recognized.');
             disp('Press any key to continue');
             %pause();
        end
        toc
    end
    % vect = round(rand(1, 25) * 1000);
    % k = insaneSearch(vect);
end

% function k = insaneSearch(vect) %Перебор всех вариантов для бинарного поиска
%     vect = sortCount(vect);
%     size = numel(vect);
%     for i = 1:size
%         k = findBinary(vect, vect(i))
%         if (k == -1)
%             disp('error');
%             exit
%         end
%     end
% end

function vect = sortBubble(vect) %Сортировка поплавком
    nswap = 0;
    size = numel(vect);
    flag = logical(1);
    i = 0;
    while ((i < (size - 1)) && flag)
        flag = 0;
        i = i + 1;
        for j = (1:size-i)
            if vect([j+1]) < vect([j])
                nswap = nswap + 1;
                vect([j j+1]) = vect([j+1 j]);
                flag = 1;
            end
        end
    end
    nswap
    vect
end

function vect = sortInsertion(vect) %Сортировка вставками
    size = numel(vect);
    nswap = 0;
    for i=2:size
        x=vect(i);
        j=i-1;
        while j>0 & x<vect(j);
            nswap = nswap + 1;
            vect(j+1)=vect(j);
            j=j-1;
            vect(j+1)=x;
        end
        for i=1:1:size
            vect(i);
        end
    end
    nswap
    vect
end

function vect = sortCount(vect) %сортировка подсчётом
     nswap = 0;
     size = numel(vect);
     countMin = min(vect);
     countMax = max(vect);
     tempVector=zeros(1,countMax-countMin+1);
     for i = (1:size)
         tempVector(vect(i) - countMin + 1) = tempVector(vect(i) - countMin + 1) + 1;
         nswap = nswap + 1;
     end
     temp = nswap;
     for i = (countMin:countMax)
         for j = (1:tempVector([i - countMin + 1]))
             nswap = nswap + 1;
             vect([nswap - temp]) = i;
         end
     end
     nswap
     vect
end

function index = findBinary(vect, key) %бинарный поиск
    index = -1;
    nview = 0;
    left = 1;
    right = numel(vect);
    while (left <= right)
        nview = nview + 1;
        mid = round(mean([left right]));
        if (key < vect([mid]))
            right = mid - 1;
        else
            if (key > vect([mid]))
                left = mid + 1;
            else
                disp('Искомый элемент: ');
                index = mid
                disp('Чимсло просмотров: ');
                nview
                return;
            end
        end

    end
    disp('Искомый элемент не найден.');
end
function index = findInterpolation(vect, key) %Интерполяционный поиск
    index = -1;
    nview = 0;
    left = 1;
    right = numel(vect) - 1;

    while ((vect([left]) <= key) && (vect([right]) >= key))
        nview = nview + 1;
        mid = floor(left + ((key - vect(left)) * (right - left)) / (vect([right]) - vect([left])));

        if (key < vect([mid]))
            right = mid - 1;
        else
            if (key > vect([mid]))
                left = mid + 1;
            else
                disp('Искомый элемент: ');
                index = mid
                disp('Чимсло просмотров: ');
                nview
                return;
            end
        end
        if (vect([left]) == key)
            disp('Искомый элемент: ');
            index = mid
            disp('Чимсло просмотров: ');
            nview
            return;
        end
    end
    disp('Искомый элемент не найден.');
end
