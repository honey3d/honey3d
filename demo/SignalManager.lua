local SignalManager = {}
SignalManager.signals = {}

function SignalManager.addCallback(self, signal, func)
   if not self.signals[signal] then self.signals[signal] = {} end
   self.signals[signal][func] = true
end

function SignalManager.removeCallback(self, signal, func)
   if self.signals[signal] then
      self.signals[signal][func] = nil
   end
end

function SignalManager.emit(self, signal, argtable)
   local sig = self.signals[signal]
   if not sig then return end

   for f, _ in pairs(sig) do
      f(argtable)
   end
end

return SignalManager
