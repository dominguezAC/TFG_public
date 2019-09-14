classdef KlongRLSE < matlab.System & matlab.system.mixin.Propagates
    % K_long synthesis from A and B 
    
    properties

    end

    properties(DiscreteState)

    end

    % Pre-computed constants
    properties(Access = private)

    end

    methods(Access = protected)
        
        
        % Propagation Methods
        function n = getOutputSizeImpl(obj)
           n = [2 4]; 
        end
        
        
        function r = isOutputFixedSizeImpl(obj)
           r = true; 
        end
        
        
        function r = getOutputDataTypeImpl(obj)
           r = 'double'; 
        end
        
        function r = isOutputComplexImpl(obj)
            r = false;
        end
        
        
        function setupImpl(obj)
            % Perform one-time calculations, such as computing constants
        end

        function K_long = stepImpl(obj,A,B)
            % Implement algorithm. Calculate y as a function of input u and
            % discrete states.
            Q = diag([10 10 5 10]); 
            R = diag([1000 100]);
            N = zeros(4,2);
            
            K_long = lqr(A,B,Q,R,N);
        end

        function resetImpl(obj)
            % Initialize / reset discrete-state properties
        end
    end
end
