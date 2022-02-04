function cs330_simple_plot(trajectoryFile, PVLO, gif, plotTitle, vectorScaling)
%cs330_simple_plot  Plotter for CS330   
%Author: Anonymous    Date: 02/12/20 (Last Updated)
%
%   cs330_simple_plot(trajectoryFile, PVLO, gif, plotTitle, vectorScaling) 
%                    Creates a plot and gif given trajectory info. 
%                    Output will be written in a folder 'simple_plot_output'
%
%   trajectoryFile = A .txt or .csv file containing trajectory information
%                    in the comma seperated form delimited by a new line,
%                    'time, characterNumber, position[1], position[2], 
%                    velocity[1], velocity[2], linear[1], linear[2], 
%                    orientation, rotation, angular\n'
%
%   PVLO           = An array of 4 bools indicating what should be plotted. 
%
%                    Passing a four element array can be used to plot some
%                    values, but not others. The bools correspond in the
%                    order [position, velocity, linear, orientation].
%
%                    For example,
%                    If an array is passed like [1,1,1,0]; 
%                    position, velocity, and linear acceleration will be 
%                    plotted, but orientation will NOT be plotted.
%
%   gif            = Either a logical 1 or a logical 0. 
%                    If 1 a gif of the plots will be automatically generated.
%                    If 0 a gif will NOT be generated.
%
%   plotTitle      = A string containing the name of physics used.
%                    This string will be used in the plot title.
%
%   vectorScaling  = A value used to lengthen or shorten all vectors
%                    lengths. 
%                    Ex. 4 or 6 are good defaults.

%Function Start

    %Print Beginning Execution
    fprintf("Plotter started...\n\n");
    
    %Check for PVLO Length
    if(length(PVLO) ~= 4)
        fprintf("Error: PVLO input array must be of length 4...\n");
        return;
    end

    %Does trajectory file exist
    if(~isfile(trajectoryFile))
        fprintf("Error: Trajectory filename does not exist...\n");
        return;
    end
    
    %Read in trajectory file
    tData = readmatrix(trajectoryFile);
    
    %Calculate number of characters
    numOfChars = 1;
    firstChar = tData(1,2);
    while(tData(numOfChars + 1, 2) ~= firstChar)
       numOfChars = numOfChars + 1;
    end
    
    %Calculate time step
    deltaT = tData(1+numOfChars,1) - tData(1,1);
    
    %Disable Warnings
    warning('off','all')
    
    %Create output directory
    status = mkdir('simple_plot_output');
    
    %Enable Warnings
    warning('on','all')
    
    %Check to see that output directory was successfully created
    if(~status)
        fprintf("Error: Unable to create output folder...\n");
        return;
    end

    %Navigate to new output directory
    oldFolder = cd('simple_plot_output');
    
    %Format title for plot
    pvloTitle = "";
    
    %Check for each var
    if(PVLO(1) == 1)
        pvloTitle = strcat(pvloTitle, "P");
    end
    if(PVLO(2) == 1)
        pvloTitle = strcat(pvloTitle, "V");
    end
    if(PVLO(3) == 1)
        pvloTitle = strcat(pvloTitle, "L");
    end
    if(PVLO(4) == 1)
        pvloTitle = strcat(pvloTitle, "O");
    end
    
    %finalTitle
    pTitle = strcat(sprintf('%s, %3.2f', plotTitle, deltaT), {' '}, pvloTitle);
        
    %Setup png name
    pngName = strcat("CS 330 20S, Plot, ", pTitle, ".png");
    
    %setup gif name
    gifName = strcat("CS 330 20S, Animated, ", pTitle, ".gif");
    
    %Are we making a gif?
    if(gif) %We are making a gif
        
        %Print Creating Gif
        fprintf("Creating gif...\n");
        
        gifFig = figure('visible', 'off');
        
        %Preallocate gif
        im{1, length(tData)*numOfChars} = [];
        
        %Add Title
        title(pTitle);

        %Format Labels
        xlabel('x');
        ylabel('z');
        xlim([-108, 108]);
        ylim([-108, 108]);

        %Format ticks
        xticks(-100:25:100);

        %Correcting z-axis
        yticks(-100:25:100);
        set(gca, 'ydir', 'reverse');
        %opengl('software');    //Did not speed up graphics rendering

        %grid on and plot ready
        grid on;
        hold on;
        
        for i = 1: numOfChars : length(tData(:,1))
            
            for j = 1: numOfChars
            
                if(PVLO(4))
                    %Orientation Vector
                    qo = quiver(tData(i+j-1, 3), -tData(i+j-1,4), sin(tData(i+j-1,9)), -cos(tData(i+j-1,9)), vectorScaling);
                    qo.Color = 'yellow';
                    qo.ShowArrowHead = 'off';
                    qo.LineWidth = 0.3;
                end

                if(PVLO(3))
                    %Linear Vector
                    ql = quiver(tData(i+j-1,3), -tData(i+j-1,4), tData(i+j-1,7), -tData(i+j-1,8), vectorScaling);
                    ql.Color = 'blue';
                    ql.ShowArrowHead = 'off';
                    ql.LineWidth = 0.3;
                end

                if(PVLO(2))
                    %Velocity Vecotor
                    qv = quiver(tData(i+j-1,3), -tData(i+j-1,4), tData(i+j-1,5), -tData(i+j-1,6), vectorScaling);
                    qv.Color = 'green';
                    qv.ShowArrowHead = 'off';
                    qv.LineWidth = 0.3;
                end
                
            end 
            
            %Prevent indexing out of an array
            if(i > numOfChars)

                for j = 1: numOfChars
                
                    if(PVLO(1))
                        %Plot Position
                        plot(tData(i+j-1-numOfChars:numOfChars:i+j-1, 3), ...
                            -tData(i+j-1-numOfChars:numOfChars:i+j-1,4), ...
                            'Color', 'red', 'LineWidth', 0.75);
                    end

                end

            end

            %Set to 1 if you want a legend in your gif. 
            %NOTE: THIS WILL SIGNIFICANTLY INCREASE EXECUTION TIME
            if(i == 1)
                
                for j = 1: numOfChars
                    
                    %Plotting Start Point
                    scatter(tData(i+j-1,3), -tData(i+j-1,4), 'red', 'filled');
                    text(tData(i+j-1,3)-15, -tData(i+j-1,4), 'start', 'Color', 'Red', 'FontSize', 10);
                    
                end
                
                legendPoints = [];
                legendNames = {};
                
                %plot dummy points for legend
                if(PVLO(1))
                    l1 = plot([NaN, NaN], 'Color', 'red');
                    legendPoints = [legendPoints l1];
                    legendNames = [legendNames 'position'];
                end
                
                if(PVLO(2))
                    l2 = plot([NaN, NaN], 'Color', 'green');
                    legendPoints = [legendPoints l2];
                    legendNames = [legendNames 'velocity'];
                end
                
                if(PVLO(3))
                    l3 = plot([NaN, NaN], 'Color', 'blue');
                    legendPoints = [legendPoints l3];
                    legendNames = [legendNames 'linear'];
                end
                
                if(PVLO(4))
                    l4 = plot([NaN, NaN], 'Color', 'yellow');
                    legendPoints = [legendPoints l4];
                    legendNames = [legendNames 'orientation'];
                end
                
                legend(legendPoints, legendNames, 'Location', 'southeast','AutoUpdate','off');

            end

            %Update Figure
            drawnow
            
            %Set Frame
            frame = getframe(gifFig);
            
            %Add to Gif
            im{i} = frame2im(frame);
         
        end
        
        for i = 1: numOfChars : length(tData(:,1))
           
            %Save Gif
            [A, map] = rgb2ind(im{i}, 256);
            
            if i == 1
                imwrite(A, map, gifName, 'gif', 'LoopCount', Inf, 'DelayTime', 0.1);
                
            else
                imwrite(A, map, gifName, 'gif', 'WriteMode', 'append', 'DelayTime', deltaT/5.0);
                
            end
            
        end
        
    end
    
    %Print Creating Gif
    fprintf("Creating png...\n");
    
    %Create hidden figure for plotting
    figurePlot = figure('visible', 'off');

    %Add Title
    title(pTitle);

    %Format Labels
    xlabel('x');
    ylabel('z');
    xlim([-108, 108]);
    ylim([-108, 108]);

    %Format ticks
    xticks(-100:25:100);

    %Correcting z-axis
    yticks(-100:25:100);
    set(gca, 'ydir', 'reverse');

    %grid on and plot ready
    grid on;
    hold on;

    %Plot Vectors
    for i = 1: length(tData(:,1))

        if(PVLO(4))
            %Orientation Vector
            qo = quiver(tData(i, 3), -tData(i,4), sin(tData(i,9)), -cos(tData(i,9)), vectorScaling);
            qo.Color = 'yellow';
            qo.ShowArrowHead = 'off';
            qo.LineWidth = 0.3;
        end

        if(PVLO(3))
            %Linear Vector
            ql = quiver(tData(i,3), -tData(i,4), tData(i,7), -tData(i,8), vectorScaling);
            ql.Color = 'blue';
            ql.ShowArrowHead = 'off';
            ql.LineWidth = 0.3;
        end

        if(PVLO(2))
            %Velocity Vecotor
            qv = quiver(tData(i,3), -tData(i,4), tData(i,5), -tData(i,6), vectorScaling);
            qv.Color = 'green';
            qv.ShowArrowHead = 'off';
            qv.LineWidth = 0.3;
        end
     
    end 
    
    for i = 1: numOfChars
        
        if(PVLO(1))
            %Plot Position
            plot(tData(i:numOfChars:end, 3), -tData(i:numOfChars:end,4), 'Color', 'red', 'LineWidth', 0.75);
        end

        %Plotting Start Point
        scatter(tData(i,3), -tData(i,4), 'red', 'filled');
        text(tData(i,3)-15, -tData(i,4), 'start', 'Color', 'Red', 'FontSize', 10);

        %Plotting End Point
        scatter(tData(end-i+1,3), -tData(end-i+1,4), 'red', 'filled');
        text(tData(end-i+1,3)-15, -tData(end-i+1,4), 'end', 'Color', 'Red', 'FontSize', 10);
        
    end
    
    legendPoints = [];
    legendNames = {};
    
    %plot dummy points for legend
    if(PVLO(1))
        l1 = plot([NaN, NaN], 'Color', 'red');
        legendPoints = [legendPoints l1];
        legendNames = [legendNames 'position'];
    end
    
    if(PVLO(2))
        l2 = plot([NaN, NaN], 'Color', 'green');
        legendPoints = [legendPoints l2];
        legendNames = [legendNames 'velocity'];
    end
    
    if(PVLO(3))
        l3 = plot([NaN, NaN], 'Color', 'blue');
        legendPoints = [legendPoints l3];
        legendNames = [legendNames 'linear'];
    end
    
    if(PVLO(4))
        l4 = plot([NaN, NaN], 'Color', 'yellow');
        legendPoints = [legendPoints l4];
        legendNames = [legendNames 'orientation'];
    end
    
    legend(legendPoints, legendNames, 'Location', 'southeast','AutoUpdate','off');
    
    %Save Plot
    saveas(figurePlot, pngName);

    %Return to parent folder
    cd(oldFolder);
    
    %Print Execution Complete
    fprintf("\nExecution Complete!\n");
    
end

