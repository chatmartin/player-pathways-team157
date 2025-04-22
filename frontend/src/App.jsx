// App.jsx
import React, { useState, useEffect } from 'react';
import axios from 'axios';
import {
  Box,
  Container,
  Typography,
  Switch,
  CircularProgress,
  Alert,
  CssBaseline,
  Paper,
  FormControlLabel,
  Button,
  Icon,
  Autocomplete,
  TextField,
} from '@mui/material';
import { styled } from '@mui/material/styles';
import PathDisplay from './components/PathDisplay';

const API_ROOT = 'http://localhost:18080';

/* ---------- menu height ( ≈ 5 rows ) ------------------------------------- */
const ITEM_HEIGHT = 48;
const MAX_LIST_HEIGHT = ITEM_HEIGHT * 5.5;

/* ---------- styled helpers ---------------------------------------------- */
const StyledPaper = styled(Paper)(({ theme }) => ({
  maxWidth: 1300,
  width: '100%',
  borderRadius: 12,
  boxShadow: theme.shadows[6],
  padding: theme.spacing(6),
  display: 'flex',
  flexDirection: 'column',
  alignItems: 'center',
  gap: theme.spacing(5),
}));

const StyledFormControlLabel = styled(FormControlLabel)(({ theme }) => ({
  marginRight: theme.spacing(4),
}));

/* an Autocomplete that takes all available width
   and forces its popper to follow the field width */
const StyledAuto = styled(Autocomplete)(({ theme }) => ({
  flex: 1,
  margin: theme.spacing(1, 0),
  '& .MuiAutocomplete-popper': {
    width: '100% !important',
  },
}));

const StyledButton = styled(Button)(({ theme }) => ({
  padding: theme.spacing(2, 5),
  fontSize: '1.2rem',
}));

const InfoBox = styled(Box)(({ theme }) => ({
  backgroundColor: '#e0f7fa',
  color: '#00acc1',
  padding: theme.spacing(2),
  borderRadius: theme.shape.borderRadius,
  textAlign: 'center',
  fontSize: '0.9rem',
  marginTop: theme.spacing(3),
  maxWidth: 850,
  width: '100%',
  boxSizing: 'border-box',
  display: 'flex',
  alignItems: 'center',
  justifyContent: 'center',
}));

/* ======================================================================== */
export default function App() {
  const [sport,         setSport]         = useState('basketball');
  const [compareAlgos,  setCompareAlgos]  = useState(true);
  const [players,       setPlayers]       = useState([]);
  const [selectedFrom,  setSelectedFrom]  = useState('');
  const [selectedTo,    setSelectedTo]    = useState('');
  const [results,       setResults]       = useState(null);
  const [error,         setError]         = useState(null);
  const [loading,       setLoading]       = useState(false);
  const [showInfoBox,   setShowInfoBox]   = useState(true);

  /* --- fetch players whenever the sport changes ------------------------- */
  useEffect(() => {
    (async () => {
      try {
        setLoading(true);
        const endpoint = sport === 'basketball' ? '/bball_graph' : '/fball_graph';
        const { data } = await axios.get(`${API_ROOT}${endpoint}`);
        setPlayers(data.players || []);
        setError(null);
      } catch {
        setError('Failed to fetch players. Please try again later.');
        setPlayers([]);
      } finally {
        setLoading(false);
      }
    })();

    /* reset state when switching sports */
    setSelectedFrom('');
    setSelectedTo('');
    setResults(null);
    setShowInfoBox(true);
  }, [sport]);

  /* --- run algorithm ----------------------------------------------------- */
  const handleSearch = async () => {
    if (!selectedFrom || !selectedTo)   return setError('Please select both players');
    if (selectedFrom === selectedTo)    return setError('Please select two different players');

    setLoading(true);
    try {
      const endpoint = sport === 'basketball' ? '/bballAlgo' : '/fballAlgo';
      const { data } = await axios.post(`${API_ROOT}${endpoint}`, {
        from: selectedFrom,
        to:   selectedTo,
      });
      setResults(data);
      setError(null);
    } catch (e) {
      setError(e.response?.data || 'An error occurred during the search');
      setResults(null);
    } finally {
      setLoading(false);
    }
  };

  /* hide / show info box */
  useEffect(() => {
    setShowInfoBox(!(selectedFrom && selectedTo && selectedFrom !== selectedTo));
  }, [selectedFrom, selectedTo]);

  /* --- common props for both Autocompletes ------------------------------ */
  const autoProps = {
    options: players,
    getOptionLabel: (o) => o?.name ?? '',
    isOptionEqualToValue: (o, v) => o.name === v.name,
    disablePortal: true,                              // popper inside Paper
    ListboxProps: { style: { maxHeight: MAX_LIST_HEIGHT } },
  };

  return (
    <Container
      disableGutters
      maxWidth={false}
      sx={{
        minHeight: '100vh',
        p: 4,
        display: 'flex',
        justifyContent: 'center',
        alignItems: 'center',
        bgcolor: '#f9fafb',
      }}
    >
      <CssBaseline />
      <StyledPaper>
        <Typography variant="h3" align="center" fontWeight={600} mb={4}>
          Player&nbsp;Connection&nbsp;Visualizer
        </Typography>

        {/* --- switches ---------------------------------------------------- */}
        <Box sx={{ display: 'flex', gap: 4, mb: 4, justifyContent: 'center', flexWrap: 'wrap' }}>
          <StyledFormControlLabel
            label={`Switch to ${sport === 'basketball' ? 'Soccer' : 'Basketball'}`}
            control={
              <Switch
                checked={sport === 'soccer'}
                onChange={() => setSport((p) => (p === 'basketball' ? 'soccer' : 'basketball'))}
              />
            }
          />
          <StyledFormControlLabel
            label="Compare both algorithms"
            control={
              <Switch
                checked={compareAlgos}
                onChange={(e) => setCompareAlgos(e.target.checked)}
              />
            }
          />
        </Box>

        {/* --- player pickers + button ------------------------------------ */}
        <Box
          sx={{
            display: 'flex',
            gap: 3,
            width: '100%',
            maxWidth: 850,
            flexWrap: 'wrap',
            justifyContent: 'center',
          }}
        >
          {/* Player A */}
          <StyledAuto
            {...autoProps}
            value={players.find((p) => p.name === selectedFrom) || null}
            onChange={(_, v) => setSelectedFrom(v ? v.name : '')}
            renderInput={(params) => (
              <TextField {...params} label="Select Player A" variant="outlined" fullWidth />
            )}
          />

          {/* Player B */}
          <StyledAuto
            {...autoProps}
            value={players.find((p) => p.name === selectedTo) || null}
            onChange={(_, v) => setSelectedTo(v ? v.name : '')}
            renderInput={(params) => (
              <TextField {...params} label="Select Player B" variant="outlined" fullWidth />
            )}
          />

          {/* search button */}
          <StyledButton
            variant="contained"
            color="primary"
            onClick={handleSearch}
            disabled={!selectedFrom || !selectedTo || selectedFrom === selectedTo || loading}
          >
            {loading ? <CircularProgress size={24} color="inherit" /> : 'Find Path'}
          </StyledButton>
        </Box>

        {showInfoBox && <InfoBox>Select two players to visualize their connection</InfoBox>}
        {!!error && (
          <Alert severity="error" sx={{ mt: 3, width: '100%', maxWidth: 850 }}>
            {error}
          </Alert>
        )}
        {loading && !results && <CircularProgress sx={{ display: 'block', mx: 'auto', mt: 4 }} />}

        {results && (
          <PathDisplay
            results={results}
            showBoth={compareAlgos}
            sx={{ mt: 4, width: '100%', maxWidth: 850 }}
          />
        )}
      </StyledPaper>
    </Container>
  );
}
